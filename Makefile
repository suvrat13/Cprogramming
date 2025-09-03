CC = gcc
CFLAGS = -Iunity -Wall -Wextra
UNITY_SRC = unity/unity.c
TEST_SRC = tests/test_practice.c
TEST_EXEC = test_practice

all: $(TEST_EXEC)

$(TEST_EXEC): $(UNITY_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TEST_EXEC)

run: $(TEST_EXEC)
	./$(TEST_EXEC)