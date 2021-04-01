### build mi-dev-env docker image

````
docker build . -t mi-dev-env
````

### make 

````
docker run -v $(pwd)/build:/home/eurorack/build mi-dev-env make -f braids/makefile
````



