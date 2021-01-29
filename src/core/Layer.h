//
// Created by Amy on 1/26/2021.
//

#ifndef DUST_LAYER_H
#define DUST_LAYER_H

#include <utility>
#include <vector>

namespace Dust {
    class Layer{
    public:
        inline static std::vector<Layer> layers;

        virtual void onAttach() = 0;
        virtual void onUpdate() = 0;
        virtual void onDestroy() = 0;
//        explicit Layer(std::string _name){
//             name = std::move(_name);
//             uuid = generateUUID();
//         };
        Layer() = default;
        virtual ~Layer() = default;
    protected:
        unsigned int getUUID(){
            return uuid;
        }

        std::string& getName(){
            return name;
        }

        void onCreate(){
            uuid = generateUUID();
        }

    private:
        unsigned int uuid{};
        std::string name;
        static unsigned int generateUUID(){
            if(!layers.empty()){
                return layers.back().uuid + 1;
            } else {
                return 1;
            }
        }
    };
}
#endif //DUST_LAYER_H
