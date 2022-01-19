#include <iostream>
#include <pybind11/pybind11.h>

#include "fft.hpp"

auto add(int i, int j) -> int
{
    return i + j;
}

auto stft_numpy(pybind11::buffer b, int fft_window, int step_size) -> Matrix *
{
    pybind11::buffer_info info = b.request();
    auto *data = static_cast<float *>(info.ptr);
    long length = info.size;

    std::cout << "ndim = " << info.ndim << std::endl;
    std::cout << "length = " << info.size << std::endl;

    return stft(Span{.buffer = data, .length = length}, fft_window, step_size);
}

PYBIND11_MODULE(pyfft, m)
{
    pybind11::class_<Matrix>(m, "Matrix", pybind11::buffer_protocol())
            .def(pybind11::init<pybind11::ssize_t, pybind11::ssize_t>())
            //Construct from a buffer
            .def(pybind11::init([](const pybind11::buffer &b) {
                pybind11::buffer_info info = b.request();
                if (info.format != pybind11::format_descriptor<float>::format() || info.ndim != 2)
                    throw std::runtime_error("Incompatible buffer format!");

                auto v = new Matrix(info.shape[0], info.shape[1]);
                memcpy(v->data(), info.ptr, sizeof(float) * (size_t) (v->rows() * v->cols()));
                return v;
            }))

            .def_buffer([](Matrix &m) -> pybind11::buffer_info {
                return pybind11::buffer_info(
                        m.data(),                                     /* Pointer to buffer */
                        sizeof(float),                                /* Size of one scalar */
                        pybind11::format_descriptor<float>::format(), /* Python struct-style format descriptor */
                        2,                                            /* Number of dimensions */
                        {m.rows(), m.cols()},                         /* Buffer dimensions */
                        {sizeof(float) * m.cols(),                    /* Strides (in bytes) for each index */
                         sizeof(float)});
            })
            .def("rows", &Matrix::rows)
            .def("cols", &Matrix::cols);


    m.def("add", &add, "A function that adds two numbers");
    m.def("stft", &stft_numpy, "stft");
}