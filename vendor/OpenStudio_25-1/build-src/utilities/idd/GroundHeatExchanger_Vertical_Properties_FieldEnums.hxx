/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_PROPERTIES_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_PROPERTIES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_Vertical_PropertiesFields
 *  \brief Enumeration of GroundHeatExchanger:Vertical:Properties's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_Vertical_PropertiesFields, )
#else
class GroundHeatExchanger_Vertical_PropertiesFields: public ::EnumBase<GroundHeatExchanger_Vertical_PropertiesFields> {
 public: 
  enum domain 
  {
Name, DepthofTopofBorehole, BoreholeLength, BoreholeDiameter, GroutThermalConductivity, GroutThermalHeatCapacity, PipeThermalConductivity, PipeThermalHeatCapacity, PipeOuterDiameter, PipeThickness, UTubeDistance,   };
  GroundHeatExchanger_Vertical_PropertiesFields()
   : EnumBase<GroundHeatExchanger_Vertical_PropertiesFields>(Name) {} 
  GroundHeatExchanger_Vertical_PropertiesFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_Vertical_PropertiesFields>(t_name) {} 
  GroundHeatExchanger_Vertical_PropertiesFields(int t_value) 
   : EnumBase<GroundHeatExchanger_Vertical_PropertiesFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_Vertical_PropertiesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_Vertical_PropertiesFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_Vertical_PropertiesFields>;
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
{ GroundHeatExchanger_Vertical_PropertiesFields::Name, "Name", "Name"},
{ GroundHeatExchanger_Vertical_PropertiesFields::DepthofTopofBorehole, "DepthofTopofBorehole", "Depth of Top of Borehole"},
{ GroundHeatExchanger_Vertical_PropertiesFields::BoreholeLength, "BoreholeLength", "Borehole Length"},
{ GroundHeatExchanger_Vertical_PropertiesFields::BoreholeDiameter, "BoreholeDiameter", "Borehole Diameter"},
{ GroundHeatExchanger_Vertical_PropertiesFields::GroutThermalConductivity, "GroutThermalConductivity", "Grout Thermal Conductivity"},
{ GroundHeatExchanger_Vertical_PropertiesFields::GroutThermalHeatCapacity, "GroutThermalHeatCapacity", "Grout Thermal Heat Capacity"},
{ GroundHeatExchanger_Vertical_PropertiesFields::PipeThermalConductivity, "PipeThermalConductivity", "Pipe Thermal Conductivity"},
{ GroundHeatExchanger_Vertical_PropertiesFields::PipeThermalHeatCapacity, "PipeThermalHeatCapacity", "Pipe Thermal Heat Capacity"},
{ GroundHeatExchanger_Vertical_PropertiesFields::PipeOuterDiameter, "PipeOuterDiameter", "Pipe Outer Diameter"},
{ GroundHeatExchanger_Vertical_PropertiesFields::PipeThickness, "PipeThickness", "Pipe Thickness"},
{ GroundHeatExchanger_Vertical_PropertiesFields::UTubeDistance, "UTubeDistance", "U-Tube Distance"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_Vertical_PropertiesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_Vertical_PropertiesFields> OptionalGroundHeatExchanger_Vertical_PropertiesFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_PROPERTIES_FIELDENUMS_HXX
