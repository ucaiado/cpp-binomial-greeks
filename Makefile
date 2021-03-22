docker-build:
	docker-compose \
	-p cpp-capstone \
	-f dcomposes/docker-compose.basic.yml \
	build

environment-test:
	cd scripts/ && bash download-data.sh && cd ..
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
