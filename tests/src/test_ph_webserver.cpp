#include <catch2/catch.hpp>
//#include <ph_concepts/concepts.hpp>
#include <ph_webserver/webserver.hpp>

using std::cout, std::endl;

TEST_CASE ("main")
{
    
    cout << "hi" << endl;
}


TEST_CASE ("read file")
{
    SECTION ("char const*")
    {
        char const* path {__FILE__};
        ph::file::read (path);
        
    }
    
    SECTION ("std::string")
    {
        
    }
}
