/*
 * Spectrum class represents intensity function value for each
 * interval of wavelengths of a visible light.
 *
 * Basically, it is a table. Constructors assume, that given values correspond
 * to the evenly spaced wavelengths starting with 380nm and ending with 740nm.
 *
 * If table size is specified, then table upscale(downscale) is managed,
 * aiming to approximate spectrum to preserve integral value.
 *
 * value_interpolated method returns intensity for any given wavelength.
 *
 * wavelengths returns all wavelengths, for which values are stored in the table.
 *
 * integral is calculating, surprise, integral of the table.
 *
 * add and multiply functions are performed for each corresponding value,
 * different table sizes are handled inside automatically.
 *
 */

#pragma once

#include <vector>

namespace core::optics
{
    class Spectrum
    {
    public:
        Spectrum(const std::vector<double>& table);
        Spectrum(const Spectrum& s, std::size_t table_size);
        Spectrum(const std::vector<double>& table, std::size_t table_size);

        double min_wavelength() const;
        double max_wavelength() const;

        std::size_t table_size() const;
        double wavelength_step() const;

        double value_interpolated(double wavelength) const;
        std::vector<double> wavelengths() const;
        double integral() const;

        void scale(double k);
        void normalize();
        void add(const Spectrum& s);
        void multiply(const Spectrum& s);

    private:
        static inline const double min_wavelength_s{380.0};
        static inline const double max_wavelength_s{740.0};

        std::vector<double> table_m;
    };
}
