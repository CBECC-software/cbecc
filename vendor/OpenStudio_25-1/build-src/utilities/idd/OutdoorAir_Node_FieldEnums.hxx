/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OUTDOORAIR_NODE_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTDOORAIR_NODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OutdoorAir_NodeFields
 *  \brief Enumeration of OutdoorAir:Node's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OutdoorAir_NodeFields, )
#else
class OutdoorAir_NodeFields: public ::EnumBase<OutdoorAir_NodeFields> {
 public: 
  enum domain 
  {
Name, HeightAboveGround, DrybulbTemperatureScheduleName, WetbulbTemperatureScheduleName, WindSpeedScheduleName, WindDirectionScheduleName, WindPressureCoefficientCurveName, SymmetricWindPressureCoefficientCurve, WindAngleType,   };
  OutdoorAir_NodeFields()
   : EnumBase<OutdoorAir_NodeFields>(Name) {} 
  OutdoorAir_NodeFields(const std::string &t_name) 
   : EnumBase<OutdoorAir_NodeFields>(t_name) {} 
  OutdoorAir_NodeFields(int t_value) 
   : EnumBase<OutdoorAir_NodeFields>(t_value) {} 
  static std::string enumName() 
  { return "OutdoorAir_NodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutdoorAir_NodeFields>::integer_value()); }
   private:
    friend class EnumBase<OutdoorAir_NodeFields>;
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
{ OutdoorAir_NodeFields::Name, "Name", "Name"},
{ OutdoorAir_NodeFields::HeightAboveGround, "HeightAboveGround", "Height Above Ground"},
{ OutdoorAir_NodeFields::DrybulbTemperatureScheduleName, "DrybulbTemperatureScheduleName", "Drybulb Temperature Schedule Name"},
{ OutdoorAir_NodeFields::WetbulbTemperatureScheduleName, "WetbulbTemperatureScheduleName", "Wetbulb Temperature Schedule Name"},
{ OutdoorAir_NodeFields::WindSpeedScheduleName, "WindSpeedScheduleName", "Wind Speed Schedule Name"},
{ OutdoorAir_NodeFields::WindDirectionScheduleName, "WindDirectionScheduleName", "Wind Direction Schedule Name"},
{ OutdoorAir_NodeFields::WindPressureCoefficientCurveName, "WindPressureCoefficientCurveName", "Wind Pressure Coefficient Curve Name"},
{ OutdoorAir_NodeFields::SymmetricWindPressureCoefficientCurve, "SymmetricWindPressureCoefficientCurve", "Symmetric Wind Pressure Coefficient Curve"},
{ OutdoorAir_NodeFields::WindAngleType, "WindAngleType", "Wind Angle Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OutdoorAir_NodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OutdoorAir_NodeFields> OptionalOutdoorAir_NodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTDOORAIR_NODE_FIELDENUMS_HXX
