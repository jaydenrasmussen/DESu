#!/bin/bash
OS="linux darwin freebsd windows"
ARCH="386 amd64"
for GOOS in $OS
do
    for GOARCH in $ARCH
    do
        echo Building bitcrypt for $GOOS $GOARCH
        go build -o $GOOS-$GOARCH-bitcrypt *.go

    done
done

GOOS=linux GOARCH=arm
echo Building bitcrypt for $GOOS $GOARCH
go build -o $GOOS-$GOARCH-bitcrypt *.go
