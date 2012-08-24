/*  bla.cpp - Copyright Peter Urban 2009

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

# include <sstream>
# include "utk/io/io.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE io_test
# include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( directory_delimiter_test )
{
  char test_delimiter = utk::io::directory_delimiter;

  BOOST_WARN_EQUAL( test_delimiter, '/' );
}

BOOST_AUTO_TEST_CASE( sequence_from_stream_test )
{
  std::stringstream test_stream( "1 2 3 4" );
  std::vector<int>  test_vector( 4 );
  utk::io::sequence_from_stream( test_stream, test_vector.begin(), test_vector.end() );
  BOOST_CHECK_EQUAL( test_vector[0], 1 );
  BOOST_CHECK_EQUAL( test_vector[1], 2 );
  BOOST_CHECK_EQUAL( test_vector[2], 3 );
  BOOST_CHECK_EQUAL( test_vector[3], 4 );

  std::stringstream test_stream2( "1 2" );
  std::vector<int>  test_vector2( 3 );
  BOOST_CHECK_THROW( utk::io::sequence_from_stream( test_stream, test_vector.begin(), test_vector.end() ), utk::io::stream_extraction_error );
}

BOOST_AUTO_TEST_CASE( sequence_from_stream_delimiter_test )
{
  std::stringstream test_stream( "1,2,3,4" );
  std::vector<int>  test_vector( 4 );
  utk::io::sequence_from_stream( test_stream, test_vector.begin(), test_vector.end(), ',' );
  BOOST_CHECK_EQUAL( test_vector[0], 1 );
  BOOST_CHECK_EQUAL( test_vector[1], 2 );
  BOOST_CHECK_EQUAL( test_vector[2], 3 );
  BOOST_CHECK_EQUAL( test_vector[3], 4 );
}

BOOST_AUTO_TEST_CASE( sequence_to_stream_delimiter_test )
{
  std::stringstream test_stream;
  std::vector<int>  test_vector{ 1, 2, 3, 4 };
  utk::io::sequence_to_stream( test_stream, test_vector.begin(), test_vector.end(), "," );
  BOOST_CHECK_EQUAL( test_stream.str(), "1,2,3,4" );
}
