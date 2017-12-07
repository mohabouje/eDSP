//
// Created by Mohammed Boujemaoui on 01/12/2017.
//

#ifndef EDSP_MAP_UTIL_H
#define EDSP_MAP_UTIL_H

#include "config.h"

#include <map>
#include <iterator>
#include <functional>
#include <array>

EDSP_BEGING_NAMESPACE
namespace utility {
    namespace map {
        namespace intern {
            template<class Map, class Predicate>
            constexpr auto count_values(const Map &map, typename Map::mapped_type const &value, const Predicate &predicate) {
                return std::count_if(map.begin(),
                                     map.end(),
                                     std::bind(predicate,
                                               std::bind(&Map::value_type::second, std::placeholders::_1), value));
            };
        }


        template<class Map>
        EDSP_EXPORT constexpr auto lower_element(const Map &map, typename Map::key_type const &key) {
            return map.lower_bound(key);
        }

        template<class Map>
        EDSP_EXPORT constexpr auto upper_element(const Map &map, typename Map::key_type const &key) {
            return map.upper_bound(key);
        }

        template<class Map>
        EDSP_EXPORT constexpr auto find_element(const Map &map, typename Map::key_type const &key) {
            return map.find(key);
        }

        template<class Map>
        EDSP_EXPORT constexpr auto find_value(const Map &map, typename Map::mapped_type const &value) {
            return std::find_if(map.begin(),
                                map.end(),
                                std::bind(std::equal_to<typename Map::mapped_type>(),
                                          std::bind(&Map::value_type::second, std::placeholders::_1), value));
        }

        template<class Map>
        EDSP_EXPORT constexpr void insert_element(Map &map, typename Map::key_type const &key, typename Map::mapped_type const &mapped) {
            auto it = map.lower_bound(key);
            map.emplace_hint(it, key, mapped);
        }


        template<class Map>
        EDSP_EXPORT constexpr void erase_element(Map &map, typename Map::value_type const &pair) {
            erase_element(map, pair.first);
        }

        template<class Map>
        EDSP_EXPORT constexpr void erase_element(Map &map, typename Map::key_type const &key) {
            auto it = map.lower_bound(key);
            if (it != map.end()) map.erase(it);
        }

        template<class Map>
        EDSP_EXPORT constexpr void erase_value(Map &map, typename Map::mapped_type const &value) {
            auto itr = map.begin();
            while (itr != map.end()) {
                if (itr->second == value) {
                    itr = map.erase(itr);
                } else {
                    ++itr;
                }
            }
        }

        template<class Map>
        EDSP_EXPORT constexpr auto count_values_equal_to(const Map &map, typename Map::mapped_type const &value) {
            return intern::count_values(map, value, std::equal_to<typename Map::mapped_type>());
        }

        template<class Map>
        EDSP_EXPORT constexpr auto count_values_less(const Map &map, typename Map::mapped_type const &value) {
            return intern::count_values(map, value, std::less<typename Map::mapped_type>());
        }

        template<class Map>
        EDSP_EXPORT constexpr auto count_values_less_equal(const Map &map, typename Map::mapped_type const &value) {
            return intern::count_values(map, value, std::less_equal<typename Map::mapped_type>());
        }

        template<class Map>
        EDSP_EXPORT constexpr auto count_values_greater(const Map &map, typename Map::mapped_type const &value) {
            return intern::count_values(map, value, std::greater<typename Map::mapped_type>());
        }

        template<class Map>
        EDSP_EXPORT constexpr auto count_values_greater_equal(const Map &map, typename Map::mapped_type const &value) {
            return intern::count_values(map, value, std::greater_equal<typename Map::mapped_type>());
        }
    }
}
EDSP_END_NAMESPACE
#endif //EDSP_MAP_UTIL_H
