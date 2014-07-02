
#ifndef __multi_array__
#define __multi_array__


#include "memory.h"


/*
**  _sizetype
*/
typedef unsigned int _sizetype;


/*
**  a template M-dimensional pointer specialized 
**  with template argument T of the outer class
**  multi_array<T, N>
*/
template<class T, _sizetype M>
class multi_ptr
{
public:
    /*
    **  recursive type definition
    **  stops at class multi_ptr<0> which defines pointer as T
    */
    typedef typename multi_ptr<T, M-1>::pointer* pointer; 
};

/*
**  stopping template class for multi_ptr
**  
*/
template<class T>
class multi_ptr<T, 0>
{
public:
    typedef T pointer;
};


/*
**  a template M-dimensional dynamic allocator specialized 
**  with template argument T of the outer class
**  multi_array<T, N>.
**  
**  it implements an M-dimensional inner allocating loops.
*/
template<class T, _sizetype M>
class multi_allocator
{
public:
    static typename multi_ptr<T, M>::pointer alloc(_sizetype* dims)
    {
        _sizetype i;
        typename multi_ptr<T, M>::pointer rtn;
        rtn=new typename multi_ptr<T, M-1>::pointer[dims[0]];
        for(i=0; i<dims[0]; i++)
            rtn[i]=multi_allocator<T, M-1>::alloc(dims+1);

        return rtn;
    }
};

/*
**  stopping template class for multi_allocator
**  
*/
template<class T>
class multi_allocator<T, 1>
{
public:
    static typename multi_ptr<T, 1>::pointer alloc(_sizetype* dims)
    {
        typename multi_ptr<T, 1>::pointer rtn;
        rtn=new T[dims[0]];
        return rtn;
    }
};



/*
**	multi_array<T, N>
**  a template N-dimensional array specializes for type T
*/
template<class T, _sizetype N>
class multi_array
{
public:
    /*
    **	N-dimensional pointer
    */
    typedef typename multi_ptr<T, N>::pointer pointer;
    
    /*
    **	N-dimensional const_pointer
    */
    typedef const pointer const_pointer;

    /*
    **  N-dimensional pointer allocator;
    */
    typedef multi_allocator<T, N> allocator;

    /*
    **  implicit casting operator to N-dimensional pointer
    */
    operator pointer(){return _pdata;}
    


    /*
    **  N-dimensional array initializing constructor 
    **  This c'tor will be removed. Different compilers
    **  and platforms have different parameter sizeof values

    multi_array(const _sizetype d1, ...)
    {
        std::cout<<sizeof(_sizetype)<<std::endl;
        std::cout<<sizeof(d1)<<std::endl;
        const _sizetype* pdims=&d1;
        memcpy(_pdims, &d1, N*sizeof(_sizetype));
        _pdata=allocator::alloc(_pdims);
    }
     */

    /*
    **  N-dimensional array initializing constructor 
    */
    multi_array(const _sizetype* pdims)
    {
        memcpy(_pdims, pdims, N*sizeof(_sizetype));
        _pdata=allocator::alloc(_pdims);
    }

protected:
    pointer _pdata;
    _sizetype _pdims[N+1];


};



#endif//__multi_array__