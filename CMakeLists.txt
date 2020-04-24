LINK_LIBRARIES(pthread)
ADD_EXECUTABLE(test.out test_ref.c kvs.c list.c kvsh.c kvsh_rwl.c)
