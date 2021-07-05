扩栈挂
#ifdef OPENSTACK
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    #if (defined _WIN64) or (defined __unix)
        __asm__("movq %0, %%rsp\n" :: "r"(p));
    #else
        __asm__("movl %0, %%esp\n" :: "r"(p));
    #endif
#endif
    注意最后加exit(0);

玄学挂
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

然后加上并行计算(计组)

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx") 