docker-build:
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.basic.yml \
	build

download-project-data:
	cd scripts/ && bash download-data.sh && cd ..

environment-test:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.basic.yml \
	run cpp

compile-program:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.justcompile.yml \
	run cpp

debug-program:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.debug.yml \
	run cpp

greeks-computation:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.yml \
	run cpp

simple-tests:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.simpletests.yml \
	run cpp
