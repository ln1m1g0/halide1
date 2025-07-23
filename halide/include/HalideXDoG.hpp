#ifndef HALIDE_XDOG_HPP
#define HALIDE_XDOG_HPP

#include "Halide.h"
#include "gaussian.hpp"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideXDoG : public Generator<HalideXDoG> {
    // TODO:
    // - Adicionar uma Func Float(32) de input e uma Func Float(32) de saída, ambas com duas dimensões
    // - Adicionar quatro GeneratorParamas (todos são do tipo float): 
    //    - sigma com valor padrão '0.5'
    //    - k com valor padrão '7.0'
    //    - gamma com valor padrão '0.95'
    //    - phi_e com valor padrão '5.0'
    // - Criar método generate que computa a XDoG descrita no protótipo no Colab [vide o README para o link]
    //    *  Use o exemplo de DoG da semana 04 como base. Não é necessário criar um generator separado para o DoG puro, apenas adiciona ao exemplo se usar
    // - Criar método schedule que seta estimativas para os valores de tamanho das dimensões dos Buffers para uso do autoscheduler

    // Dica: não é necessário explicitar padding aqui pois a Func que deve ser entrada já está coberta por uma BoundaryCondition

    public:
        
	Input<Func> img_input{"img_input_dog", Float(32), 2};

        GeneratorParam<float> sigma{"sigma", 0.5f};
        GeneratorParam<float> k{"k", 7.0f};
        GeneratorParam<float> gamma{"gamma", 0.95f};
	GeneratorParam<float> phi{"roughness", 5.0f};

        
        Output<Func> img_output{"img_output_dog", Float(32), 2};

        void generate() {
            
	    input_bound(x,y) = img_input(x,y);
            

            Expr lk_width = get_kernel_width(sigma.value());
            Expr hk_width = get_kernel_width(k.value() * sigma.value());

            Expr low_sigma = sigma;
            Expr high_sigma = k * low_sigma;
            weights_low(i) = gaussian(i, low_sigma);
            weights_high(i) = gaussian(i, high_sigma);

            RDom rd_low(-(lk_width / 2), lk_width, -(lk_width / 2), lk_width);
            RDom rd_high(-(hk_width / 2), hk_width, -(hk_width / 2), hk_width);

            
            Expr pixel_low = input_bound(x + rd_low.x, y + rd_low.y);
            Expr sum_low = sum(weights_low(rd_low.x) * weights_low(rd_low.y), "sum_low");
            filtered_low(x, y) = sum(
                pixel_low * weights_low(rd_low.x) * weights_low(rd_low.y), "sum_conv_low"
            ) / sum_low;
            

            
            Expr pixel_high = input_bound(x + rd_high.x, y + rd_high.y);
            Expr sum_high = sum(weights_high(rd_high.x) * weights_high(rd_high.y), "sum_high");
            filtered_high(x, y) = sum(
                pixel_high * weights_high(rd_high.x) * weights_high(rd_high.y), "sum_conv_high"
            ) / sum_high;

            
             dog(x, y) = filtered_low(x, y) - gamma * filtered_high(x, y);
             img_output(x, y) = (
                select(
                    (dog(x, y)) > 0.0f, 
                    1.0f, 
                    1.0f*(1+tanh(phi*(dog(x, y))))
                )
            );
        }

        void schedule() {
            if (using_autoscheduler()) {
                img_input.set_estimates({{0, 1920}, {0, 1920}});
                img_output.set_estimates({{0, 1920}, {0, 1920}});
            }
        }

    private:
        Var x{"x"}, y{"y"}, c{"c"}, i{"i"};
        Func input_bound{"input_bound"};
        Func weights_low{"weights_low"}, weights_high{"weights_high"};
        Func filtered_low{"filtered_low"}, filtered_high{"filtered_high"};
        
        
        Func dog{"DoG"};


};
#endif
