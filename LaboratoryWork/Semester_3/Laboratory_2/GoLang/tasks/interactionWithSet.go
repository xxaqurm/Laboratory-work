package tasks

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strings"
)

type Set struct {
	data map[string]struct{}
}

func NewSet() *Set {
	return &Set{data: make(map[string]struct{})}
}

func (s *Set) Add(elm string) {
	s.data[elm] = struct{}{}
}

func (s *Set) Remove(elm string) {
	delete(s.data, elm)
}

func (s *Set) Contains(elm string) bool {
	_, exists := s.data[elm]
	return exists
}

func (s *Set) GetElements() []string {
	elms := make([]string, 0, len(s.data))
	for k := range s.data {
		elms = append(elms, k)
	}
	return elms
}

func parseLine(query string) []string {
	parts := strings.Fields(query)
	return parts
}

func InteractionWithSet(args []string) error {
	var filename, command, structName, data string

	if len(args) >= 5 && args[1] == "--file" && args[3] == "--query" {
		filename = args[2]
		queryParts := parseLine(args[4])
		if len(queryParts) != 3 {
			return errors.New("неверное количество аргументов в query")
		}
		command = queryParts[0]
		structName = queryParts[1]
		data = queryParts[2]
	} else {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Введите имя файла: ")
		fname, _ := reader.ReadString('\n')
		filename = strings.TrimSpace(fname)

		fmt.Print("Введите команду (SETADD, SETDEL, SET_AT): ")
		cmd, _ := reader.ReadString('\n')
		command = strings.TrimSpace(cmd)

		fmt.Print("Введите имя структуры: ")
		stname, _ := reader.ReadString('\n')
		structName = strings.TrimSpace(stname)

		fmt.Print("Введите данные: ")
		d, _ := reader.ReadString('\n')
		data = strings.TrimSpace(d)
	}

	if _, err := os.Stat(filename); os.IsNotExist(err) {
		f, err := os.Create(filename)
		if err != nil {
			return fmt.Errorf("ошибка при создании файла: %v", err)
		}
		f.Close()
	}

	fileData := make(map[string][]string)
	file, err := os.Open(filename)
	if err != nil {
		return fmt.Errorf("ошибка при открытии файла: %v", err)
	}
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := parseLine(line)
		if len(parts) > 0 {
			fileData[parts[0]] = append([]string{}, parts[1:]...)
		}
	}
	file.Close()

	st := NewSet()
	if values, ok := fileData[structName]; ok {
		for _, v := range values {
			st.Add(v)
		}
	}

	switch command {
	case "SETADD":
		st.Add(data)
	case "SETDEL":
		st.Remove(data)
	case "SET_AT":
		if st.Contains(data) {
			fmt.Println("Элемент присутствует в множестве")
		} else {
			fmt.Println("Элемент отсутствует в множестве")
		}
	default:
		return fmt.Errorf("неизвестная команда: %s", command)
	}

	fileData[structName] = st.GetElements()
	out, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("ошибка при записи в файл: %v", err)
	}
	defer out.Close()

	writer := bufio.NewWriter(out)
	for key, values := range fileData {
		fmt.Fprint(writer, key)
		for _, v := range values {
			fmt.Fprintf(writer, " %s", v)
		}
		fmt.Fprintln(writer)
	}
	writer.Flush()

	return nil
}