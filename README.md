# 📖 get_next_line

<p align="center">
  Read a file descriptor line by line  
  <br>
  <i>42 School Project · C · Static Storage · File Descriptors</i>
</p>

---

## 📌 Overview

`get_next_line` is a function that reads from a file descriptor and returns **one line at a time**.

This implementation is based on:

* low-level reading with `read`
* a static storage buffer between calls
* dynamic string concatenation
* newline detection and buffer splitting

---

## ⚙️ Function Prototype

```c
char	*get_next_line(int fd);
```

The goal of the project is to return:

* the next line from the file descriptor
* including `\n` when present
* or `NULL` when there is nothing left to read or when an error occurs. ([GitHub][1])

---

## 🧩 Project Structure

```bash
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
```

---

## 🛠️ Implementation Details

### `get_next_line.c`

This file contains the main logic of the project.

#### Core behavior

* checks invalid cases:

  * `BUFFER_SIZE <= 0`
  * `fd < 0`
* duplicates the static stored remainder into `buffer`
* reads from the file descriptor until a newline is found or EOF is reached
* splits the full buffer into:

  * the line to return
  * the remaining unread part stored for the next call

#### Internal helper functions

**`ft_newline`**

* searches for `\n` inside a string
* returns its index
* returns `-1` if no newline is found

**`split_buffer_store`**

* separates the current line from the remaining unread content
* copies everything after `\n` into the static `store`
* truncates the current line after the newline

**`read_and_append`**

* reads chunks of size `BUFFER_SIZE`
* appends them to `buffer`
* stops when:

  * a newline is found
  * `read` returns `0` (EOF)
  * `read` returns `< 0` (error)

---

### `get_next_line_utils.c`

This file contains the helper functions used by the main function:

* `ft_strlen`
* `ft_strdup`
* `ft_strjoin`
* `ft_bzero`
* `ft_strlcpy`

These are custom utility functions used instead of relying on libft, which matches the expected project structure for `get_next_line`. ([GitHub][2])

---

### `get_next_line.h`

The header file contains:

* required includes
* the `BUFFER_SIZE` definition
* function prototypes

Current default:

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
```

This means the project works both:

* with a default buffer size
* and with `-D BUFFER_SIZE=n` at compile time, which is how 42 commonly evaluates the project. ([GitHub][1])

---

## 🔄 How It Works

```txt
stored remainder
      ↓
ft_strdup(store)
      ↓
read_and_append()
      ↓
newline found ?
   ├── yes → split_buffer_store()
   └── no  → keep reading until EOF
      ↓
return one complete line
```

---

## ✨ Behavior of This Implementation

### Static storage

This project uses:

```c
static char	store[BUFFER_SIZE + 1] = {0};
```

So the function keeps unread content between calls.

### Newline handling

* if a newline is found, the returned string includes it
* the rest is saved in `store`

### EOF handling

* if no more data is available and the buffer is empty, the function returns `NULL`

### Error handling

* if `read` fails, allocated memory is freed and `NULL` is returned

### Buffer growth

* each new chunk read from the file is appended using `ft_strjoin`

---

## ⚠️ Important Note

This implementation uses **one static buffer only**:

```c
static char	store[BUFFER_SIZE + 1];
```

That means it is designed for the **mandatory version**, not the multi-file-descriptor bonus version.

So:

* ✅ works for standard line-by-line reading
* ❌ does not independently store leftover data for multiple file descriptors

---

## 🚀 Compilation

Compile with the default buffer size:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

Compile with a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Using `-D BUFFER_SIZE=n` is part of the expected project compilation style. ([GitHub][1])

---

## 💡 Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

---

## 📚 Allowed External Functions

For the mandatory project, the expected external functions are:

```txt
read
malloc
free
```

This implementation follows that model in its core logic. ([GitHub][1])

---

## 🎯 Learning Outcomes

Through this project, I practiced:

* file descriptor handling
* static variables
* dynamic memory allocation
* string manipulation
* newline-based parsing
* defensive error handling

---

## 👤 Author

**Psyche0920**
GitHub: https://github.com/Psyche0920

[1]: https://github.com/f-corvaro/GET_NEXT_LINE?utm_source=chatgpt.com "GitHub - f-corvaro/GET_NEXT_LINE: \"Line-by-Line File Reader\""
[2]: https://github.com/augustobecker/get_next_line?utm_source=chatgpt.com "GitHub - augustobecker/get_next_line: A C function that reads any valid file line by line - @42sp Project"
