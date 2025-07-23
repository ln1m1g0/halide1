#ifndef HALIDE_ELEMENTWISE_MULT
#define HALIDE_ELEMENTWISE_MULT

#include "Halide.h"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideElementwiseMult : public Generator<HalideElementwiseMult> {
    // TODO:
    // - Adicionar duas Funcs Float(32) de input e uma Func Float(32) de saída, todas com duas dimensões
    // - Criar método generate que computa o produto entre os pixels das duas Funcs de entrada e salva na saída
    // - Criar método schedule que seta estimativas para os valores de tamanho das dimensões dos Buffers para uso do autoscheduler
    public:
        /*Input<Buffer<uint8_t>> img_input_quantize{"img_input_quantize", 2};
        Input<Buffer<uint8_t>> img_input_dog{"img_input_dog", 2};
        Output<Buffer<uint8_t>> img_output_mult{"img_output_mult", 2};*/
        
        Input<Func> img_input_quantize{"img_input_quantize", Float(32), 2};
        Input<Func> img_input_dog{"img_input_dog", Float(32), 2};
        Output<Func> img_output{"img_output_mult", Float(32), 2};
        
                
        void generate() {
        
        	img_output(x,y) = img_input_dog(x,y)*img_input_quantize(x,y);        	
                
        }
        void schedule() {
        	if (using_autoscheduler()) {
                    img_input_quantize.set_estimates({{0, 1920}, {0, 1920}});
                    img_input_dog.set_estimates({{0, 1920}, {0, 1920}});
                    img_output.set_estimates({{0, 1920}, {0, 1920}});
            	} else {
                    // inline computation
            	}
        }
        
    private:
        Var x{"x"}, y{"y"}; 
};

#endif
