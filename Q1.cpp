
/*NAME : UNZILA ANJUM
ROLL NO : 22i-2550
SECTION : A
---ASSIGNMENT # 03---*/


//QUESTION NO 1

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Block {
private:
    string shape_; //for shapes
    string color_; // for colors of the sahpe
public:
    //Constructor with default parameters 
    Block(string shape = "", string color = "") : shape_(shape), color_(color) {}

    //getters 
    string getShape() const { 
        return shape_;
    }
    string getColor() const { 
        return color_;
    }
    //setters for setting the shape and color
    void setShape(string shape) {
        shape_ = shape;
    }
    void setColor(string color) {
        color_ = color;
    }

    //friend function definition of overloading << to display the blocks
    friend ostream& operator<<(ostream& out, const Block& block);
};

// function definition
ostream& operator<<(ostream& out, const Block& block) {
    if (!block.color_.empty()) {
        out << "(" << block.shape_ << ", " << block.color_ << ")";
    }
    else {
        out << block.shape_;
    }
    return out;
}

class Build {
private:
    int height_;
    int width_;
    int depth_;
    Block*** content_;  //3D array to point the blocks object to build
public:
    // constructor that takes a Block object as a parameter
    //and creates a build with a single layer containing that block
    Build(const Block& block) : height_(1), depth_(1), width_(1) {
        content_ = new Block * *[height_];
        content_[0] = new Block * [depth_];
        content_[0][0] = new Block[block.getShape().size()];

        for (int i = 0; i < block.getShape().size(); ++i) {
            content_[0][0][i] = block;
        }
    }
    // destructor to deallocate the memory which is taken by the 3D array of content
    ~Build() {
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < depth_; ++j) {
                delete[] content_[i][j];
            }
            delete[] content_[i];
        }
        delete[] content_;
    }
    // overloading << function definition for printing the build
    friend ostream& operator<<(ostream& out, const Build& build);

    Build& operator^=(const Block& block) {
        // create a new content array with increased height
        Block*** new_content = new Block * *[height_ + 1];
        for (int i = 0; i < height_ + 1; ++i) {
            new_content[i] = new Block * [depth_];
            for (int j = 0; j < depth_; ++j) {
                new_content[i][j] = new Block[width_];
            }
        }

        // copy existing content to the new array
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < depth_; ++j) {
                for (int k = 0; k < width_; ++k) {
                    new_content[i][j][k] = content_[i][j][k];
                }
            }
        }

        // fill the new layer with the new block
        for (int j = 0; j < depth_; ++j) {
            for (int k = 0; k < width_; ++k) {
                new_content[height_][j][k] = block;
            }
        }

        // delete the old content and replace it with the new one
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < depth_; ++j) {
                delete[] content_[i][j];
            }
            delete[] content_[i];
        }
        delete[] content_;

        content_ = new_content;
        ++height_;

        return *this;
    }

    Build operator^(const Block& block) const {
        Build result(*this);
        result ^= block;
        return result;
    }


// function definition of the << overloading function
    friend ostream& operator<<(ostream& out, const Build& build) {
        for (int i = build.height_ - 1; i >= 0; --i) {
            out << "Layer " << i + 1 << ":" << endl;
            for (int j = 0; j < build.depth_; ++j) {
                for (int k = 0; k < build.width_; ++k) {
                    out << setw(10) << build.content_[i][j][k];
                }
                out << endl;
            }
            out << endl;
        }
        return out;
    }
};

int main() {
    Block ObliquedL("ObliquedL", "red");
    Block ObliquedR("ObliquedR", "red");
    Block Simple("simple", "red");
    Block SimpleW("simple", "white");

    Build tower(ObliquedL);
    std::cout << tower << std::endl;

    tower ^= ObliquedR;
    std::cout << tower << std::endl;

    tower ^= Simple;
    std::cout << tower << std::endl;
    tower ^= SimpleW;
    std::cout << tower << std::endl;

    return 0;
}
