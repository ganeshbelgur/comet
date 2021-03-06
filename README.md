# Comet

Comet is an open source photo realistic 3D rendering software. It is based on the popular Monte Carlo method of rendering images of three-dimensional scenes such that the global illumination is faithful to reality. It is also a research-oriented rendering system that aims to develop cutting edge techniques one day. The aim is to help artists in the visual effects and animation industries to create spectacular lifelike images for the big screen and for the new age mediums such as VR, AR, etc.

![Comet Cornell Box Render](docs/renders/comet-cornell-box.jpg)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

Before starting, it is important to note that at the moment:
* Comet is supported only on Linux and we hope to support other platforms soon.
* Comet doesn't support any three-dimensional scene description file formats such as USD, Alembic, etc. So, the scenes need to be hard coded in the test cases for rendering purposes.

### Building from source

1. We use the good old GNU Make for building the source code at the moment. To build the code, you'll need to simply run the make command at the root directory of the project.

```bash
make
```

2. This builds all the object files and the main executable, named `comet`, under the newly created `bin/` folder. To clean the build i.e. to delete the `bin/` folder and all the `*.o` files, run the command:

```bash
make clean
```

3. To see the source files that is going to be compiled, run the command:

```bash
make help
```

### Running the program

Once you are done building the executable called `comet` from the source, you are good to execute it.
To run the executable, use the following command at the project's root directory:

```bash
./bin/comet > nameOfMyScene.ppm
```

The final product of any renderer is an image file and comet currently outputs the color information of each pixel of the image in the PPM file standard. The color information needs to be redirected into a PPM file to be able to view it from any standard Linux image viewers. The rendered image is of the hard coded scene in the program at the time of building.

## Contributing

Comet is in very early stages of development. However, we welcome your pull requests, ideas and suggestions!

Please read [CONTRIBUTING](docs/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us. The coding standards for writing C++ code are described in detail at [CPPSTANDARDS](docs/CPPSTANDARDS.md)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/ganeshbelgur/comet/tags).

## Authors

* **Ganesh Belgur** - *Initial work* - [ganeshbelgur](https://github.com/ganeshbelgur)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* "Ray Tracing in One Weekend" books by Peter Shirley
* "Physically Based Rendering: From Theory to Implementation" by Matt Pharr, Wenzel Jakob and Greg Humphreys
* "TU Wien Rendering / Ray Tracing Course" by Károly Zsolnai and Thomas Auzinger
