package main

import (
	"io/ioutil"
	"log"

	"github.com/jdeng/jbig2enc"
)

func main() {
	data, err := ioutil.ReadFile("1.bmp")
	if err != nil {
		log.Fatal(err)
	}

	out, err := jbig2enc.Encode(data)
	if err != nil {
		log.Fatal(err)
	}

	ioutil.WriteFile("1.jb2", out, 0644)
}
