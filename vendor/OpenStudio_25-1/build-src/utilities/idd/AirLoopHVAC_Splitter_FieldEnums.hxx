/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_SPLITTER_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_SPLITTER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_SplitterFields
 *  \brief Enumeration of AirLoopHVAC:Splitter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_SplitterFields, )
#else
class AirLoopHVAC_SplitterFields: public ::EnumBase<AirLoopHVAC_SplitterFields> {
 public: 
  enum domain 
  {
Name, InletNodeName,   };
  AirLoopHVAC_SplitterFields()
   : EnumBase<AirLoopHVAC_SplitterFields>(Name) {} 
  AirLoopHVAC_SplitterFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SplitterFields>(t_name) {} 
  AirLoopHVAC_SplitterFields(int t_value) 
   : EnumBase<AirLoopHVAC_SplitterFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SplitterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SplitterFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SplitterFields>;
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
{ AirLoopHVAC_SplitterFields::Name, "Name", "Name"},
{ AirLoopHVAC_SplitterFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SplitterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SplitterFields> OptionalAirLoopHVAC_SplitterFields ;
#endif

/** \class AirLoopHVAC_SplitterExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:Splitter's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_SplitterExtensibleFields, )
#else
class AirLoopHVAC_SplitterExtensibleFields: public ::EnumBase<AirLoopHVAC_SplitterExtensibleFields> {
 public: 
  enum domain 
  {
OutletNodeName,   };
  AirLoopHVAC_SplitterExtensibleFields()
   : EnumBase<AirLoopHVAC_SplitterExtensibleFields>(OutletNodeName) {} 
  AirLoopHVAC_SplitterExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SplitterExtensibleFields>(t_name) {} 
  AirLoopHVAC_SplitterExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_SplitterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SplitterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SplitterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SplitterExtensibleFields>;
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
{ AirLoopHVAC_SplitterExtensibleFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SplitterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SplitterExtensibleFields> OptionalAirLoopHVAC_SplitterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_SPLITTER_FIELDENUMS_HXX
