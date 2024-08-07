CFLAGS = -c -Wall -Werror -Wextra -std=c11 
LDFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard s21_*.c)
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
TESTS_SOURCE = test.c
TESTS_OBJECTS = $(patsubst %.c,%.o, ${TESTS_SOURCE})
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
	BREW = .
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB =
	BREW := ${HOME}/homebrew
endif

PATH := $(BREW)/bin:$(PATH)

all: s21_string.a

s21_string.a: ${SOURCE}
	$(CC) $(CFLAGS) $(ADD_LIB) $(SOURCE)
	ar rc $@ $(OBJECTS)
	ranlib $@
	-rm -rf *.o

test: ${TESTS_SOURCE} s21_string.a
	${CC} $(LDFLAGS) -o test $^ -lcheck
	./test

gcov_report: ${SOURCE}
	gcc --coverage ${SOURCE} ${TESTS_SOURCE} -o gcov_test -lcheck
	chmod +x gcov_test
	./gcov_test
	lcov -t "gcov_test" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif

valgrind: clean
	make s21_string.a
	gcc -g ${TESTS_SOURCE} s21_string.a -o test -lcheck -lcheck -lpthread -D_GNU_SOURCE 
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./test

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf ./test
	-rm -rf s21_test
	-rm -rf RESULT_VALGRIND.txt

rebuild: clean all
.PHONY: all clean check lcov
