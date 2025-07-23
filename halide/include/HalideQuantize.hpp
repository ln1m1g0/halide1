#ifndef HALIDE_QUANTIZE
#define HALIDE_QUANTIZE

#include "Halide.h"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideQuantize : public Generator<HalideQuantize> {
    // TODO:
    // - Adicionar uma Func Float(32) de input e uma Func Float(32) de saída, ambas com duas dimensões
    // - Adicionar dois GeneratorParamas: um int chamado levels com valor padrão '10' e um float chamado phi_q com valor padrão '0.25'
    // - Criar método generate que computa a quantiza descrita no protótipo no Colab [vide o README para o link]
    // - Criar método schedule que seta estimativas para os valores de tamanho das dimensões dos Buffers para uso do autoscheduler
    public:
                
        Input<Func> img_input_quantize{"img_input_quantize", Float(32), 2};
	    Output<Func> img_output_quantize{"img_output_quantize", Float(32), 2};
              
        GeneratorParam<int> levels{"levels", 10};
        GeneratorParam<float> phi_q{"phi_q", 0.25f};
        
        void generate() {
        	
        	Expr step = 100.0f/f32(levels);
        	q_nearest(x,y) = floor(img_input_quantize(x,y)/step)*step;
        	img_output_quantize(x,y) = q_nearest(x,y) + 
        	    (step/2.0f)*tanh(phi_q*(img_input_quantize(x,y) - q_nearest(x,y)));
                
        }
        void schedule() {
        	if (using_autoscheduler()) {
                    img_input_quantize.set_estimates({{0, 1920}, {0, 1920}});
                    img_output_quantize.set_estimates({{0, 1920}, {0, 1920}});
            	} else {
                    // inline computation
            	}
        }
        
    private:
        Var x{"x"}, y{"y"}, c{"c"}, i{"i"};
        Func q_nearest{"q_nearest"}; 

};

#endif

