#pragma once
#include <mutex>
#include <iterator>
#include <array>
#include <map>

template <class T, size_t MaxElements>
class CircleBuffer
{
	using _container = std::array<T, MaxElements>;
	using _iterator = typename _container::iterator;

	// inner buf
	_container _buffer;

	// tail iterator
	_iterator _tail{ _buffer.begin() };

	// map of id and offset
	std::map<size_t, _iterator> _offset_info_map;

	// sync for buffer
	std::mutex _bufferMutex;

	//
	void circ_advance(_iterator & iterator, size_t distance)
	{
		while(distance--)
			rewind_to_begin_if_end(++iterator);
	}

	//
	void check_offset(const _iterator& previous_tail, _iterator &it)
	{
		// do not check client with current id
		// we will do it later
		if (previous_tail > _tail)
		{
			if (it > previous_tail || it <= _tail)
			{
				it = _tail;
				rewind_to_begin_if_end(++it);
			}
		}
		else
		{
			if (it > previous_tail && it <= _tail)
			{
				it = _tail;
				rewind_to_begin_if_end(++it);
			}
		}
	}

	// return true if was rewinded
	bool rewind_to_begin_if_end(_iterator& it)
	{
		const auto was = (it == _buffer.end());
		if (was)
			it = _buffer.begin();
		return was;
	}

	//
	void check_offsets(const size_t client_id, const _iterator& previous_tail)
	{
		for (auto & info : _offset_info_map)
		{
			// do not check client with current id
			// we will do it later
			if (info.first != client_id)
				check_offset(previous_tail, info.second);
		}
	}

	void copy_linear(T *io_buffer, const size_t count, _iterator & tail_previous)
	{
		// copy data to the previous tail position
		auto pending_copy_size = count;
		auto data_it = io_buffer;
		while (pending_copy_size)
		{
			const auto distance_from_tail_to_end = static_cast<size_t>(std::distance(tail_previous, _buffer.end()));
			const auto real_copy_size = pending_copy_size > distance_from_tail_to_end ? distance_from_tail_to_end : pending_copy_size;
			std::copy(data_it, data_it + real_copy_size, tail_previous);
			circ_advance(tail_previous, real_copy_size);
			pending_copy_size -= real_copy_size;
			data_it += real_copy_size;
		}
	}

public:

	// Adds data to the buffer and return count of data
	size_t Sync(T *io_buffer, const size_t count, const size_t max_count, const size_t client_id)
	{
		std::lock_guard<std::mutex>lc(_bufferMutex);

		// count must be less than max_count or equal
		if (count > max_count || count >= MaxElements)
			return 0u;

		// copy previous tail position
		auto tail_previous = _tail;

		// advance tail
		circ_advance(_tail, count);

		// check all offsets and set the equal to the tail if they become invalid
		check_offsets(client_id, tail_previous);

		// initialize return value,count of elements after synchronization
		size_t r_count = 0u;

		// find client 
		typename std::map<size_t, _iterator>::iterator &client_info_it = _offset_info_map.find(client_id);
		if (client_info_it == _offset_info_map.end())
		{
			// if client doesn't exist 
			// create client info with current tail 
			_offset_info_map.emplace(client_id, _tail);
			// 
			copy_linear(io_buffer, count, tail_previous);
			//
			r_count = count;
		}
		else
		{
			// completely new data, no need to sync,  return the same 
			if (tail_previous == client_info_it->second)
			{
				// copy from previous tail
				copy_linear(io_buffer, count, tail_previous);
				// set current tail
				client_info_it->second = _tail;
				// set return value
				r_count = count;
			}
			else
			{
				// count of elements available to copy from buffer
				auto estimated_distance = count;
				auto stupid_offset = client_info_it->second;
				while (stupid_offset != tail_previous)
				{
					rewind_to_begin_if_end(++stupid_offset);
					++estimated_distance;
				}

				for (auto data_it = 0u; data_it < estimated_distance && data_it < max_count; ++data_it, r_count = data_it)
				{
					if (data_it < count)
					{
						// copy from data to the tail_previous
						(*tail_previous) = io_buffer[data_it];
						// advance by 1 _tail iterator
						rewind_to_begin_if_end(++tail_previous);
					}

					// copy from client offset to the io buffer
					io_buffer[data_it] = *(client_info_it->second);

					// advance client iterator
					rewind_to_begin_if_end(++(client_info_it->second));

				}
			}
		}
		return r_count;
	}

};
