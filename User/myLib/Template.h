#ifndef     __X_TEMPLATE_H
#define     __X_TEMPLATE_H

#include <stdint.h>

namespace myLib
{
    template<typename InputIterator, typename Functor>
    inline void foreach(InputIterator iterator_start, InputIterator iterator_end, Functor fun)
    {
        while (iterator_start != iterator_end)
        {
            fun(*iterator_start);
            iterator_start ++;
        }
    }

    template<typename InputIterator, typename Functor1>
    inline void foreach(InputIterator iterator_start, uint32_t size, Functor1 fun)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            fun(*iterator_start);
            iterator_start ++;
        }
    }

    template<typename InputIterator, typename OutputIterator, typename FilterFunctor>
    inline uint32_t filter(OutputIterator out, InputIterator in, uint32_t size, FilterFunctor fun)
    {
        uint32_t len = 0;
        for (uint32_t i = 0; i < size; i ++)
        {
            if (fun(*in))
            {
                *out = *in;
                out ++;
                len ++;
            }
            in ++;
        }
        return len;
    }

    template<typename InputIterator, typename OutputIterator, typename MapFunctor>
    inline void map(OutputIterator out, InputIterator in, uint32_t size, MapFunctor fun)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            *out = fun(*in);
            out ++;
            in ++;
        }
    }

    template<typename InputIterator, typename EqualFunctor>
    inline bool equal(InputIterator iterator1, InputIterator iterator2, uint32_t size, EqualFunctor fun)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            if (!fun(*iterator1, *iterator2))
            {
                return false;
            }
            iterator1 ++;
            iterator2 ++;
        }
        return true;
    }

    template<typename InputIterator, typename OutputIterator>
    inline void copy(OutputIterator out, InputIterator begin, InputIterator end)
    {
        while (begin < end)
        {
            *out = *begin;
            out ++;
            begin ++;
        }
    }

    template<typename InputIterator, typename OutputInterator>
    inline void copy(OutputInterator out, InputIterator begin, uint32_t size)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            *out = *begin;
            out ++;
            begin ++;
        }
    }

    template<typename OutputIterator, typename Functor>
    inline void init(OutputIterator begin, uint32_t size, Functor fun)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            *begin = fun();
            begin ++;
        }
    }

    template<typename OutputInterator, typename Functor>
    inline void initIndexed(OutputInterator begin, uint32_t size, Functor fun)
    {
        for (uint32_t i = 0; i < size; i ++)
        {
            *begin = fun(i);
            begin ++;
        }
    }

    template<typename OutputIterator, typename Functor>
    inline void init(OutputIterator begin, OutputIterator end, Functor fun)
    {
        while (begin < end)
        {
            *begin = fun();
            begin ++;
        }
    }
}





#endif
