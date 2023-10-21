#include <ShapeType.hpp>

std::map<std::tuple<ImVec4, float>, std::shared_ptr<ColorShapeType>, CompareTuple> ColorShapeTypeFactory::colorShapeCache = {};
