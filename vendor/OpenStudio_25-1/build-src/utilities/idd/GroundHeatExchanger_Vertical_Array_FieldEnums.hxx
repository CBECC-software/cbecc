/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_ARRAY_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_ARRAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_Vertical_ArrayFields
 *  \brief Enumeration of GroundHeatExchanger:Vertical:Array's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_Vertical_ArrayFields, )
#else
class GroundHeatExchanger_Vertical_ArrayFields: public ::EnumBase<GroundHeatExchanger_Vertical_ArrayFields> {
 public: 
  enum domain 
  {
Name, GHE_Vertical_PropertiesObjectName, NumberofBoreholesinXDirection, NumberofBoreholesinYDirection, BoreholeSpacing,   };
  GroundHeatExchanger_Vertical_ArrayFields()
   : EnumBase<GroundHeatExchanger_Vertical_ArrayFields>(Name) {} 
  GroundHeatExchanger_Vertical_ArrayFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_Vertical_ArrayFields>(t_name) {} 
  GroundHeatExchanger_Vertical_ArrayFields(int t_value) 
   : EnumBase<GroundHeatExchanger_Vertical_ArrayFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_Vertical_ArrayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_Vertical_ArrayFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_Vertical_ArrayFields>;
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
{ GroundHeatExchanger_Vertical_ArrayFields::Name, "Name", "Name"},
{ GroundHeatExchanger_Vertical_ArrayFields::GHE_Vertical_PropertiesObjectName, "GHE_Vertical_PropertiesObjectName", "GHE:Vertical:Properties Object Name"},
{ GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinXDirection, "NumberofBoreholesinXDirection", "Number of Boreholes in X-Direction"},
{ GroundHeatExchanger_Vertical_ArrayFields::NumberofBoreholesinYDirection, "NumberofBoreholesinYDirection", "Number of Boreholes in Y-Direction"},
{ GroundHeatExchanger_Vertical_ArrayFields::BoreholeSpacing, "BoreholeSpacing", "Borehole Spacing"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_Vertical_ArrayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_Vertical_ArrayFields> OptionalGroundHeatExchanger_Vertical_ArrayFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_ARRAY_FIELDENUMS_HXX
