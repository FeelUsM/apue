#!/usr/bin/env python3
import socket

servers = [
	("tcpbin.com", 4242),
	("tcpbin.com", 4243),
]

local_port = 50000  # любой фиксированный свободный локальный порт

for host, port in servers:
	print(f"Connecting to {host}:{port} ...")

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(("0.0.0.0", local_port))
	s.connect((host, port))

	# читаем приветствие и свой src порт
	data = s.recv(1024).decode(errors="ignore")
	s.close()

	# ищем "Your port: XXXXX"
	for line in data.splitlines():
		if "port" in line.lower():
			print(" ", line)
	print()
