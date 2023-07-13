set(SRC_FILES
        MemoryBlockAllocator.cpp
	utils.cpp
        )

# Создание библиотеки из исходных файлов
add_library(PoolAllocator ${SRC_FILES})

# Добавление директории с заголовочными файлами для поиска
target_include_directories(PoolAllocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)