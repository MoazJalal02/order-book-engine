#ifndef VOLUME_AT_PRICE_HPP
#define VOLUME_AT_PRICE_HPP

class VolumeAtPrice {
    private:
        double price;
        double buyVolume;
        double sellVolume;
    
    public:
        VolumeAtPrice(double, double, double);
        void setBuyVolume(double);
        void setSellVolume(double);
        double getBuyVolume();
        double getSellVolume();
};

#endif