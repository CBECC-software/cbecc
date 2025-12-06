/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CONSTRUCTIONPROPERTY_INTERNALHEATSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_CONSTRUCTIONPROPERTY_INTERNALHEATSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ConstructionProperty_InternalHeatSourceFields
 *  \brief Enumeration of ConstructionProperty:InternalHeatSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ConstructionProperty_InternalHeatSourceFields, )
#else
class ConstructionProperty_InternalHeatSourceFields: public ::EnumBase<ConstructionProperty_InternalHeatSourceFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, ThermalSourcePresentAfterLayerNumber, TemperatureCalculationRequestedAfterLayerNumber, DimensionsfortheCTFCalculation, TubeSpacing, TwoDimensionalTemperatureCalculationPosition,   };
  ConstructionProperty_InternalHeatSourceFields()
   : EnumBase<ConstructionProperty_InternalHeatSourceFields>(Name) {} 
  ConstructionProperty_InternalHeatSourceFields(const std::string &t_name) 
   : EnumBase<ConstructionProperty_InternalHeatSourceFields>(t_name) {} 
  ConstructionProperty_InternalHeatSourceFields(int t_value) 
   : EnumBase<ConstructionProperty_InternalHeatSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "ConstructionProperty_InternalHeatSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ConstructionProperty_InternalHeatSourceFields>::integer_value()); }
   private:
    friend class EnumBase<ConstructionProperty_InternalHeatSourceFields>;
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
{ ConstructionProperty_InternalHeatSourceFields::Name, "Name", "Name"},
{ ConstructionProperty_InternalHeatSourceFields::ConstructionName, "ConstructionName", "Construction Name"},
{ ConstructionProperty_InternalHeatSourceFields::ThermalSourcePresentAfterLayerNumber, "ThermalSourcePresentAfterLayerNumber", "Thermal Source Present After Layer Number"},
{ ConstructionProperty_InternalHeatSourceFields::TemperatureCalculationRequestedAfterLayerNumber, "TemperatureCalculationRequestedAfterLayerNumber", "Temperature Calculation Requested After Layer Number"},
{ ConstructionProperty_InternalHeatSourceFields::DimensionsfortheCTFCalculation, "DimensionsfortheCTFCalculation", "Dimensions for the CTF Calculation"},
{ ConstructionProperty_InternalHeatSourceFields::TubeSpacing, "TubeSpacing", "Tube Spacing"},
{ ConstructionProperty_InternalHeatSourceFields::TwoDimensionalTemperatureCalculationPosition, "TwoDimensionalTemperatureCalculationPosition", "Two-Dimensional Temperature Calculation Position"},
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
  inline std::ostream &operator<<(std::ostream &os, const ConstructionProperty_InternalHeatSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ConstructionProperty_InternalHeatSourceFields> OptionalConstructionProperty_InternalHeatSourceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONSTRUCTIONPROPERTY_INTERNALHEATSOURCE_FIELDENUMS_HXX
