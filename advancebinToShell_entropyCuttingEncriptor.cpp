#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdint>




const char* dictionery[256] = {
    "acid", "aqua", "arch", "area", "army", "atom", "aura", "auto", "axis", "baby", "back", "ball", "bank", "base", "bath", "beam",
    "bean", "bear", "beef", "bell", "belt", "best", "bike", "bill", "bird", "blue", "boat", "body", "bomb", "bond", "bone", "book",
    "boom", "boot", "boss", "bowl", "box", "boy", "burn", "bus", "busy", "cake", "call", "calm", "camp", "can", "card", "care",
    "case", "cash", "cat", "cave", "cell", "cent", "chef", "city", "clan", "clay", "clip", "club", "coal", "coat", "code", "coil",
    "coin", "cold", "coma", "cook", "cool", "copy", "cord", "core", "corn", "cost", "crew", "crop", "cube", "cup", "curl", "cut",
    "dark", "data", "date", "dawn", "dead", "deal", "dear", "debt", "deck", "deep", "deer", "desk", "dial", "dice", "diet", "dig",
    "dirt", "disc", "dish", "disk", "dog", "doll", "door", "dose", "dot", "down", "draw", "drop", "drum", "dual", "duck", "due",
    "dust", "duty", "each", "ear", "east", "easy", "edge", "egg", "eight", "else", "end", "epic", "era", "even", "ever", "exit",
    "face", "fact", "fair", "fall", "fan", "far", "farm", "fast", "fate", "fear", "feel", "feet", "fell", "felt", "file", "fill",
    "film", "find", "fine", "fire", "firm", "fish", "five", "fix", "flag", "flat", "flow", "fly", "foam", "focus", "fog", "food",
    "foot", "ford", "fork", "form", "fort", "four", "free", "frog", "from", "fuel", "full", "fund", "game", "gang", "gas", "gate",
    "gear", "gem", "gift", "girl", "give", "glad", "glass", "glow", "goal", "goat", "gold", "golf", "good", "grab", "gray", "grid",
    "grin", "grip", "grow", "gulf", "gum", "guy", "hair", "half", "hall", "halo", "hand", "hang", "hard", "hat", "have", "head",
    "heal", "hear", "heat", "help", "herb", "here", "hero", "high", "hill", "hint", "hip", "hire", "hit", "hold", "hole", "holy",
    "home", "hope", "host", "hot", "hour", "house", "huge", "hull", "hum", "hunt", "hurt", "ice", "icon", "idea", "idle", "inch",
    "index", "ink", "inner", "input", "into", "iris", "iron", "is", "island", "item", "jade", "jar", "jaw", "jazz", "jean", "jet"
};
unsigned char rotate_left(unsigned char val, int shift) {
    shift %= 8;
    return (val << shift) | (val >> (8 - shift));
}

unsigned char matrix_encript(uint32_t k, size_t x, unsigned char S_t, unsigned char B_t) {

    unsigned char roll_key = k;
    roll_key = rotate_left(roll_key ^ x, x % 7);
    // rotate_left logic here...
    unsigned char byte = (B_t ^ roll_key) + S_t;
    return byte;
}


int main(int arguc , char* arguv[]){

    uint32_t key = 0x7809687;
    unsigned char last_enc = 0x8369320;
     
    if(arguc < 2){

        std::cout<<"usage:"<<arguv[0]<<"file.bin"<<std::endl;

        return 1;
    }

    std::ifstream binery(arguv[1] , std::ios::binary | std::ios::ate);

    if(!binery.is_open()){

        std::cout<<"error while opening the file"<<std::endl;
        return 1;
    }

    std::streamsize size = binery.tellg();
    binery.seekg(0 , std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if(!binery.read(reinterpret_cast<char*>(buffer.data()) , size)){

       std::cout<<"couldn't find the file"<<std::endl;
       return 1;

    }
      for(auto& byte : buffer){
        byte = ~byte;
      }
      std::cout<<"\"";
     unsigned char encrip_byte;
     

    for(size_t i =0 ; i < buffer.size(); ++i){
        
        encrip_byte = matrix_encript(key , size , last_enc, buffer[i]);//this part will encript the code
    
            std::cout << dictionery[encrip_byte] << " ";
            last_enc = encrip_byte;
        
        if ((i + 1) % 10 == 0) std::cout << "\"\n\"";
    }
           std::cout << "\";" << std::endl;

     std::cout<<"\""<<std::endl;
        std::cout<<"the size of the file is"<<std::dec<<size<<std::endl;

   return 1;

}
  


     
         
    


   


