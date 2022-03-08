/*
	cat /proc/`psidof ./memfd`/maps

7fca70b44000-7fca70b4a000 rw-p 00000000 00:00 0
7fca70b67000-7fca70b68000 rwxs 00000000 00:05 19960170                   /memfd:xyz (deleted)
7fca70b68000-7fca70b69000 rwxs 00000000 00:05 19960169                   /memfd:abc (deleted)
7fca70b69000-7fca70b6a000 r--p 00029000 103:03 19136541                  /lib/x86_64-linux-gnu/ld-2.27.so
7fca70b6a000-7fca70b6b000 rw-p 0002a000 103:03 19136541                  /lib/x86_64-linux-gnu/ld-2.27.so
*/
#define XBYAK_USE_MEMFD
#include <xbyak/xbyak.h>

class Code : Xbyak::MmapAllocator, public Xbyak::CodeGenerator {
public:
    Code(const char *name, int v)
        : Xbyak::MmapAllocator(name)
        , Xbyak::CodeGenerator(4096, nullptr, this /* specify external MmapAllocator */)
    {
        mov(eax, v);
        ret();
    }
};

int main()
{
    Code c1("abc", 123);
    Code c2("xyz", 456);
    printf("c1 %d\n", c1.getCode<int (*)()>()());
    printf("c2 %d\n", c2.getCode<int (*)()>()());
    getchar();
}
