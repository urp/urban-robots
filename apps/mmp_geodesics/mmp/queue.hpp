/***************************************************************************
 *            mmp-queue.h
 *
 *  Fri Apr  9 14:58:17 2010
 *  Copyright  2010  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

# pragma once

//# define DBG_FLAT_MMP_RRIORITY_QUEUE_VALUES
//# define DBG_FLAT_MMP_RRIORITY_QUEUE_SORTING

# include <vector>
# include <functional>
# include <iostream>
# include <algorithm>


namespace mmp
{
  // priority queue which allows deletion of elements
  template<typename T, typename Container = std::vector<T>,  typename Compare = std::less<T> >
  class PriorityQueue
  {
    public:

      typedef Container container_t;

      typedef typename container_t::value_type value_type;

      typedef typename container_t::iterator		iterator;
      typedef typename container_t::const_iterator    	const_iterator;
      typedef typename container_t::reverse_iterator		reverse_iterator;
      typedef typename container_t::const_reverse_iterator	const_reverse_iterator;

      typedef typename container_t::reference		reference;
      typedef typename container_t::const_reference	const_reference;
      typedef typename container_t::pointer           	pointer;
      typedef typename container_t::difference_type   	difference_type;
      typedef typename container_t::size_type         	size_type;

      container_t	container;
      Compare         	compare;

      PriorityQueue( const Compare& comp = Compare() )
      : container(), compare( comp )
      {	}

      //iterators

      iterator begin() { return container.begin(); }

      const_iterator begin() const { return container.begin(); }

      iterator end() { return container.end(); }

      const_iterator end() const { return container.end(); }

      reverse_iterator rbegin() { return container.rbegin(); }

      const_reverse_iterator rbegin() const { return container.rbegin(); }

      reverse_iterator rend() { return container.rend(); }

      const_reverse_iterator rend() const { return container.rend(); }

      const bool empty() const { return container.empty(); }

      const size_t size() const { return container.size(); }

      reference top()
      {
	assert( not empty() );
	return container.front();
      }

      const_reference top() const
      {
	assert( not empty() );
	return container.front();
      }

      value_type pop()
      {
	value_type v = top();
	std::pop_heap( container.begin(), container.end(), compare );
	container.pop_back();
	return v;
      }

      const_reference push( const_reference v )
      {
	# if defined DBG_FLAT_MMP_RRIORITY_QUEUE_VALUES
	std::clog << "mmp::PriorityQueue::push\t\t|"
		  << " value " << v << std::endl;
	# endif
	container.push_back( v );
	std::push_heap( container.begin(), container.end(), compare );
	return v;
      }

      void remove( const_reference v )
      {
	# if defined DBG_FLAT_MMP_RRIORITY_QUEUE_VALUES
	std::clog << "mmp::PriorityQueue::remove\t\t|" << " value " << v << std::endl;
	# endif

	container.remove(v);

	std::make_heap( container.begin(), container.end(), compare );
      }

      template<class Predicate>
      void remove_if( const Predicate& pred )
      {
	erase( std::remove_if( container.begin(), container.end(), pred), container.end() );
      }

      void erase( iterator loc )
      {
	# if defined DBG_FLAT_MMP_RRIORITY_QUEUE_VALUES
	std::clog << "mmp::PriorityQueue::erase\t\t|"
		  << " value " << *loc << std::endl;
	# endif
	container.erase(loc);
	std::make_heap( container.begin(), container.end(), compare );
      }

      void erase( iterator first, iterator last )
      {
	container.erase(first, last);
	std::make_heap( container.begin(), container.end(), compare );
      }
  };
}
