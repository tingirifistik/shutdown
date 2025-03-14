package main

import (
	"fmt"
	"os/exec"
	"runtime"
	"time"
)

func main() {
	var shell, arg1, arg2, cancel string
	var timeMultiplier int

	if runtime.GOOS == "linux" {
		shell = "sh"
		arg1 = "-c"
		arg2 = "shutdown -h +"
		cancel = "shutdown -c"
		timeMultiplier = 1
	} else if runtime.GOOS == "windows" {
		shell = "cmd"
		arg1 = "/C"
		arg2 = "shutdown -s -f -t "
		cancel = "shutdown -a"
		timeMultiplier = 60
	}

	for {
		fmt.Print("\033[H\033[2J")
		fmt.Print("1- Set the shutdown time\n2- Cancel the shutdown\n3- Exit\n\n>>>")
		var menu int
		fmt.Scan(&menu)
		fmt.Print("\033[H\033[2J")
		switch menu {
		case 1:
			fmt.Print("How many minutes later do you want the computer to shutdown: ")
			var minutes int
			fmt.Scan(&minutes)
			shutdownTime := timeMultiplier * minutes
			exec.Command(shell, arg1, fmt.Sprintf("%s%d", arg2, shutdownTime)).Run()
		case 2:
			exec.Command(shell, arg1, cancel).Run()
			fmt.Println("The shutdown has been canceled..")
			time.Sleep(2 * time.Second)
		case 3:
			return
		default:
			fmt.Println("Please make a valid choice..")
			time.Sleep(2 * time.Second)
		}
	}
}
