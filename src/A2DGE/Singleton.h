/** 
 * @file Singleton.h
 *
 * @author Rohin Knight
 * @brief Implementation of the Singleton design pattern.
 */
//============================================================================
#ifndef Singleton_H_
#define Singleton_H_
//============================================================================
namespace A2DGE {
//============================================================================
template< class T >
class Singleton
{
public:
    static T* getPtr()
    {
        static T m_Instance;
        return &m_Instance;
    }

private:
    Singleton();
    ~Singleton();
    Singleton( Singleton const& );
    Singleton& operator=( Singleton const& );
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Singleton_H_*/
//============================================================================
