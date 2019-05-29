// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace srs { namespace par4
{
    struct crast {};

}} //namespace srs::par4

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace crast
    {

            static const double XM = 0.97720502380583984317;
            static const double RXM = 1.02332670794648848847;
            static const double YM = 3.06998012383946546542;
            static const double RYM = 0.32573500793527994772;
            //static const double third = 0.333333333333333333;

            // template class, using CRTP to implement forward/inverse
            template <typename T, typename Parameters>
            struct base_crast_spheroid
                : public base_t_fi<base_crast_spheroid<T, Parameters>, T, Parameters>
            {
                inline base_crast_spheroid(const Parameters& par)
                    : base_t_fi<base_crast_spheroid<T, Parameters>, T, Parameters>(*this, par)
                {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(T& lp_lon, T& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third = detail::third<T>();

                    lp_lat *= third;
                    xy_x = XM * lp_lon * (2. * cos(lp_lat + lp_lat) - 1.);
                    xy_y = YM * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(T& xy_x, T& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T third = detail::third<T>();

                    lp_lat = 3. * asin(xy_y * RYM);
                    lp_lon = xy_x * RXM / (2. * cos((lp_lat + lp_lat) * third) - 1);
                }

                static inline std::string get_name()
                {
                    return "crast_spheroid";
                }

            };

            // Craster Parabolic (Putnins P4)
            template <typename Parameters>
            inline void setup_crast(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::crast
    #endif // doxygen

    /*!
        \brief Craster Parabolic (Putnins P4) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_crast.gif
    */
    template <typename T, typename Parameters>
    struct crast_spheroid : public detail::crast::base_crast_spheroid<T, Parameters>
    {
        inline crast_spheroid(const Parameters& par) : detail::crast::base_crast_spheroid<T, Parameters>(par)
        {
            detail::crast::setup_crast(this->m_par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(srs::par4::crast, crast_spheroid, crast_spheroid)

        // Factory entry(s)
        template <typename T, typename Parameters>
        class crast_entry : public detail::factory_entry<T, Parameters>
        {
            public :
                virtual base_v<T, Parameters>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<crast_spheroid<T, Parameters>, T, Parameters>(par);
                }
        };

        template <typename T, typename Parameters>
        inline void crast_init(detail::base_factory<T, Parameters>& factory)
        {
            factory.add_to_factory("crast", new crast_entry<T, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP

