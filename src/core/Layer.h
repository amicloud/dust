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
        virtual void onMouseEvent(){};
//        explicit Layer(std::string _name){
//             name = std::move(_name);
//             uid = generateUID();
//         };
        Layer() = default;
        virtual ~Layer() = default;
    protected:
        unsigned int getUUID(){
            return uid;
        }

        std::string& getName(){
            return name;
        }

        void onCreate(){
            uid = generateUID();
        }

    private:
        unsigned int uid{};
        std::string name;
        static unsigned int generateUID(){
            if(!layers.empty()){
                return layers.back().uid + 1;
            } else {
                return 1;
            }
        }
    };
}
#endif //DUST_LAYER_H
