# 프로그램 이름
TARGET = CC-Converter

# 소스 파일들
SRCS = main.c userio.c message.c autodetect.c

# 오브젝트 파일들 (자동 변환)
OBJS = $(SRCS:.c=.o)

# 사용 라이브러리
LIBS = -lopencc

# 컴파일러 및 옵션
CC = gcc
CFLAGS = -Wall -Wextra -O2

# 기본 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# .c 파일을 .o로 컴파일
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 깨끗하게 청소
clean:
	rm -f $(TARGET) $(OBJS)

# 강제 리빌드
rebuild: clean all

.PHONY: all clean rebuild

