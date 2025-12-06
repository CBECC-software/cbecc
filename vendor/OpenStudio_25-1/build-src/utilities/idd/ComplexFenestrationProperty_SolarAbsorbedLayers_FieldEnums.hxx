/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COMPLEXFENESTRATIONPROPERTY_SOLARABSORBEDLAYERS_FIELDENUMS_HXX
#define UTILITIES_IDD_COMPLEXFENESTRATIONPROPERTY_SOLARABSORBEDLAYERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ComplexFenestrationProperty_SolarAbsorbedLayersFields
 *  \brief Enumeration of ComplexFenestrationProperty:SolarAbsorbedLayers's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ComplexFenestrationProperty_SolarAbsorbedLayersFields, )
#else
class ComplexFenestrationProperty_SolarAbsorbedLayersFields: public ::EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields> {
 public: 
  enum domain 
  {
Name, FenestrationSurface, ConstructionName, Layer1SolarRadiationAbsorbedScheduleName, Layer2SolarRadiationAbsorbedScheduleName, Layer3SolarRadiationAbsorbedScheduleName, Layer4SolarRadiationAbsorbedScheduleName, Layer5SolarRadiationAbsorbedScheduleName,   };
  ComplexFenestrationProperty_SolarAbsorbedLayersFields()
   : EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields>(Name) {} 
  ComplexFenestrationProperty_SolarAbsorbedLayersFields(const std::string &t_name) 
   : EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields>(t_name) {} 
  ComplexFenestrationProperty_SolarAbsorbedLayersFields(int t_value) 
   : EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields>(t_value) {} 
  static std::string enumName() 
  { return "ComplexFenestrationProperty_SolarAbsorbedLayersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields>::integer_value()); }
   private:
    friend class EnumBase<ComplexFenestrationProperty_SolarAbsorbedLayersFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Name, "Name", "Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::FenestrationSurface, "FenestrationSurface", "Fenestration Surface"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::ConstructionName, "ConstructionName", "Construction Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Layer1SolarRadiationAbsorbedScheduleName, "Layer1SolarRadiationAbsorbedScheduleName", "Layer 1 Solar Radiation Absorbed Schedule Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Layer2SolarRadiationAbsorbedScheduleName, "Layer2SolarRadiationAbsorbedScheduleName", "Layer 2 Solar Radiation Absorbed Schedule Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Layer3SolarRadiationAbsorbedScheduleName, "Layer3SolarRadiationAbsorbedScheduleName", "Layer 3 Solar Radiation Absorbed Schedule Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Layer4SolarRadiationAbsorbedScheduleName, "Layer4SolarRadiationAbsorbedScheduleName", "Layer 4 Solar Radiation Absorbed Schedule Name"},
{ ComplexFenestrationProperty_SolarAbsorbedLayersFields::Layer5SolarRadiationAbsorbedScheduleName, "Layer5SolarRadiationAbsorbedScheduleName", "Layer 5 Solar Radiation Absorbed Schedule Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const ComplexFenestrationProperty_SolarAbsorbedLayersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ComplexFenestrationProperty_SolarAbsorbedLayersFields> OptionalComplexFenestrationProperty_SolarAbsorbedLayersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COMPLEXFENESTRATIONPROPERTY_SOLARABSORBEDLAYERS_FIELDENUMS_HXX
