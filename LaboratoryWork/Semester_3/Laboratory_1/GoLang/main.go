package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laboratory_1/ds/dynamicArray"
	"laboratory_1/ds/forwardList"
	"laboratory_1/ds/linkedList"
	"laboratory_1/ds/queue"
	"laboratory_1/ds/stack"
)

func loadTextDB(path string) map[string][]string {
	db := make(map[string][]string)

	file, err := os.Open(path)
	if err != nil {
		return db
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}
		name := parts[0]
		values := parts[1:]
		db[name] = values
	}

	return db
}

func saveTextDB(path string, db map[string][]string) {
	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for name, values := range db {
		line := name
		if len(values) > 0 {
			line += " " + strings.Join(values, " ")
		}
		writer.WriteString(line + "\n")
	}
	writer.Flush()
}

func parseInt(s string) int {
	n, _ := strconv.Atoi(s)
	return n
}

func listToStrings(ll *linkedlist.LinkedList[int]) []string {
	res := []string{}
	for _, v := range ll.Read() {
		res = append(res, strconv.Itoa(v))
	}
	return res
}

func stringsToList(vals []string) *linkedlist.LinkedList[int] {
	ll := linkedlist.New[int]()
	for _, s := range vals {
		ll.PushBack(parseInt(s))
	}
	return ll
}

func forwardListToStrings(fl *forwardlist.ForwardList[int]) []string {
	res := []string{}
	for _, v := range fl.Read() {
		res = append(res, strconv.Itoa(v))
	}
	return res
}

func stringsToForwardList(vals []string) *forwardlist.ForwardList[int] {
	fl := forwardlist.New[int]()
	for _, s := range vals {
		fl.PushBack(parseInt(s))
	}
	return fl
}

func stackToStrings(s *stack.Stack[int]) []string {
	res := []string{}
	for _, v := range s.Read() {
		res = append(res, strconv.Itoa(v))
	}
	return res
}

func stringsToStack(vals []string) *stack.Stack[int] {
	s := stack.New[int]()
	for _, v := range vals {
		s.Push(parseInt(v))
	}
	return s
}

func queueToStrings(q *queue.Queue[int]) []string {
	res := []string{}
	for _, v := range q.Read() {
		res = append(res, strconv.Itoa(v))
	}
	return res
}

func stringsToQueue(vals []string) *queue.Queue[int] {
	q := queue.New[int]()
	for _, v := range vals {
		q.Push(parseInt(v))
	}
	return q
}

func arrayToStrings(arr *dynamicarray.DynamicArray[int]) []string {
	res := []string{}
	for _, v := range arr.Read() {
		res = append(res, strconv.Itoa(v))
	}
	return res
}

func stringsToArray(vals []string) *dynamicarray.DynamicArray[int] {
	arr := dynamicarray.New[int]()
	for _, v := range vals {
		arr.PushBack(parseInt(v))
	}
	return arr
}

func main() {
	file := flag.String("file", "data.db", "Path to data file")
	query := flag.String("query", "", "Command to execute")
	flag.Parse()

	if *query == "" {
		fmt.Println("Error: missing --query argument")
		os.Exit(1)
	}

	db := loadTextDB(*file)

	llists := make(map[string]*linkedlist.LinkedList[int])
	flists := make(map[string]*forwardlist.ForwardList[int])
	stacks := make(map[string]*stack.Stack[int])
	queues := make(map[string]*queue.Queue[int])
	arrays := make(map[string]*dynamicarray.DynamicArray[int])

	for name, vals := range db {
		switch {
		case strings.HasPrefix(name, "ll"):
			llists[name] = stringsToList(vals)
		case strings.HasPrefix(name, "fl"):
			flists[name] = stringsToForwardList(vals)
		case strings.HasPrefix(name, "s"):
			stacks[name] = stringsToStack(vals)
		case strings.HasPrefix(name, "q"):
			queues[name] = stringsToQueue(vals)
		case strings.HasPrefix(name, "a"):
			arrays[name] = stringsToArray(vals)
		}
	}

	args := strings.Fields(*query)
	if len(args) == 0 {
		fmt.Println("Empty query")
		return
	}
	cmd := strings.ToUpper(args[0])

	switch cmd {

	case "LPUSHHEAD":
		name, val := args[1], parseInt(args[2])
		if llists[name] == nil {
			llists[name] = linkedlist.New[int]()
		}
		llists[name].PushFront(val)
		db[name] = listToStrings(llists[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "LPUSHTAIL":
		name, val := args[1], parseInt(args[2])
		if llists[name] == nil {
			llists[name] = linkedlist.New[int]()
		}
		llists[name].PushBack(val)
		db[name] = listToStrings(llists[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "LPRINT":
		name := args[1]
		if llists[name] == nil {
			fmt.Println("List not found")
			return
		}
		fmt.Println(llists[name].Read())
	case "LDELELM":
		name, val := args[1], parseInt(args[2])
		if llists[name] == nil {
			fmt.Println("List not found")
			return
		}
		if llists[name].RemoveByValue(val) {
			db[name] = listToStrings(llists[name])
			saveTextDB(*file, db)
			fmt.Println("OK")
		} else {
			fmt.Println("NOT FOUND")
		}

	case "FPUSHHEAD":
		name, val := args[1], parseInt(args[2])
		if flists[name] == nil {
			flists[name] = forwardlist.New[int]()
		}
		flists[name].PushFront(val)
		db[name] = forwardListToStrings(flists[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "FPUSHTAIL":
		name, val := args[1], parseInt(args[2])
		if flists[name] == nil {
			flists[name] = forwardlist.New[int]()
		}
		flists[name].PushBack(val)
		db[name] = forwardListToStrings(flists[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "FPRINT":
		name := args[1]
		if flists[name] == nil {
			fmt.Println("List not found")
			return
		}
		fmt.Println(flists[name].Read())
	case "FDELELM":
		name, val := args[1], parseInt(args[2])
		if flists[name] == nil {
			fmt.Println("List not found")
			return
		}
		if flists[name].RemoveByValue(val) {
			db[name] = forwardListToStrings(flists[name])
			saveTextDB(*file, db)
			fmt.Println("OK")
		} else {
			fmt.Println("NOT FOUND")
		}

	case "SPUSH":
		name, val := args[1], parseInt(args[2])
		if stacks[name] == nil {
			stacks[name] = stack.New[int]()
		}
		stacks[name].Push(val)
		db[name] = stackToStrings(stacks[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "SPOP":
		name := args[1]
		if stacks[name] == nil {
			fmt.Println("Stack not found")
			return
		}
		val, ok := stacks[name].Pop()
		if !ok {
			fmt.Println("EMPTY")
			return
		}
		db[name] = stackToStrings(stacks[name])
		saveTextDB(*file, db)
		fmt.Println(val)
	case "SPRINT":
		name := args[1]
		if stacks[name] == nil {
			fmt.Println("Stack not found")
			return
		}
		fmt.Println(stacks[name].Read())

	case "QPUSH":
		name, val := args[1], parseInt(args[2])
		if queues[name] == nil {
			queues[name] = queue.New[int]()
		}
		queues[name].Push(val)
		db[name] = queueToStrings(queues[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "QPOP":
		name := args[1]
		if queues[name] == nil {
			fmt.Println("Queue not found")
			return
		}
		val, ok := queues[name].Pop()
		if !ok {
			fmt.Println("EMPTY")
			return
		}
		db[name] = queueToStrings(queues[name])
		saveTextDB(*file, db)
		fmt.Println(val)
	case "QPRINT":
		name := args[1]
		if queues[name] == nil {
			fmt.Println("Queue not found")
			return
		}
		fmt.Println(queues[name].Read())

	case "APUSHBACK":
		name, val := args[1], parseInt(args[2])
		if arrays[name] == nil {
			arrays[name] = dynamicarray.New[int]()
		}
		arrays[name].PushBack(val)
		db[name] = arrayToStrings(arrays[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "AINSERT":
		name, idx, val := args[1], parseInt(args[2]), parseInt(args[3])
		if arrays[name] == nil {
			arrays[name] = dynamicarray.New[int]()
		}
		if err := arrays[name].Insert(idx, val); err != nil {
			fmt.Println("Index out of bounds")
			return
		}
		db[name] = arrayToStrings(arrays[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "AGETELM":
		name, idx := args[1], parseInt(args[2])
		if arrays[name] == nil {
			fmt.Println("Array not found")
			return
		}
		val, err := arrays[name].Get(idx)
		if err != nil {
			fmt.Println("Index out of bounds")
			return
		}
		fmt.Println(val)
	case "ADELELM":
		name, idx := args[1], parseInt(args[2])
		if arrays[name] == nil {
			fmt.Println("Array not found")
			return
		}
		if err := arrays[name].Delete(idx); err != nil {
			fmt.Println("Index out of bounds")
			return
		}
		db[name] = arrayToStrings(arrays[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "AREPLACE":
		name, idx, val := args[1], parseInt(args[2]), parseInt(args[3])
		if arrays[name] == nil {
			fmt.Println("Array not found")
			return
		}
		if err := arrays[name].Set(idx, val); err != nil {
			fmt.Println("Index out of bounds")
			return
		}
		db[name] = arrayToStrings(arrays[name])
		saveTextDB(*file, db)
		fmt.Println("OK")
	case "AGETSIZE":
		name := args[1]
		if arrays[name] == nil {
			fmt.Println(0)
			return
		}
		fmt.Println(arrays[name].Len())
	case "APRINT":
		name := args[1]
		if arrays[name] == nil {
			fmt.Println("Array not found")
			return
		}
		fmt.Println(arrayToStrings(arrays[name]))

	default:
		fmt.Println("Unknown command:", cmd)
	}
}