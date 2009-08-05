/*
 *  Advertise (test for multicast)
 *
 *  Copyright(c) 2009 Red Hat Middleware, LLC,
 *  and individual contributors as indicated by the @authors tag.
 *  See the copyright.txt in the distribution for a
 *  full listing of individual contributors.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library in the file COPYING.LIB;
 *  if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * @author Jean-Frederic Clere
 */

#include "apr.h"
#include "apr_network_io.h"
#include "apr_strings.h"

int main(int argc, char **argv)
{
    apr_pool_t *pool;
    apr_status_t rv;
    apr_sockaddr_t   *ma_mgroup_sa;
    apr_socket_t     *ma_mgroup_socket;

    apr_initialize();
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);

    rv = apr_sockaddr_info_get(&ma_mgroup_sa, "224.0.1.105", APR_INET, 23364, APR_UNSPEC, pool);
    if (rv != APR_SUCCESS) {
        printf("apr_sockaddr_info_get failed %d\n", rv);
        return 1;
    }

    rv = apr_socket_create(&ma_mgroup_socket, ma_mgroup_sa->family, SOCK_DGRAM, APR_PROTO_UDP, pool);
    if (rv != APR_SUCCESS) {
        printf("apr_socket_create failed %d\n", rv);
        return 1;
    }
    rv = apr_mcast_join(ma_mgroup_socket, ma_mgroup_sa, NULL, NULL);
    if (rv != APR_SUCCESS) {
        printf("apr_mcast_join failed %d\n", rv);
        return 1;
    }



    return 0;
}
