### make mi-dev-env docker image

````
docker build . -t mi-dev-env
````

### make firmware

````
docker run -v $(pwd):/home/eurorack/build mi-dev-env make -f braids/makefile
````

