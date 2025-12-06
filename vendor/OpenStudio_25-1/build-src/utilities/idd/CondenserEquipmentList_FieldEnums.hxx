/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CONDENSEREQUIPMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_CONDENSEREQUIPMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CondenserEquipmentListFields
 *  \brief Enumeration of CondenserEquipmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CondenserEquipmentListFields, )
#else
class CondenserEquipmentListFields: public ::EnumBase<CondenserEquipmentListFields> {
 public: 
  enum domain 
  {
Name,   };
  CondenserEquipmentListFields()
   : EnumBase<CondenserEquipmentListFields>(Name) {} 
  CondenserEquipmentListFields(const std::string &t_name) 
   : EnumBase<CondenserEquipmentListFields>(t_name) {} 
  CondenserEquipmentListFields(int t_value) 
   : EnumBase<CondenserEquipmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "CondenserEquipmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CondenserEquipmentListFields>::integer_value()); }
   private:
    friend class EnumBase<CondenserEquipmentListFields>;
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
{ CondenserEquipmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const CondenserEquipmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CondenserEquipmentListFields> OptionalCondenserEquipmentListFields ;
#endif

/** \class CondenserEquipmentListExtensibleFields
 *  \brief Enumeration of CondenserEquipmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(CondenserEquipmentListExtensibleFields, )
#else
class CondenserEquipmentListExtensibleFields: public ::EnumBase<CondenserEquipmentListExtensibleFields> {
 public: 
  enum domain 
  {
EquipmentObjectType, EquipmentName,   };
  CondenserEquipmentListExtensibleFields()
   : EnumBase<CondenserEquipmentListExtensibleFields>(EquipmentObjectType) {} 
  CondenserEquipmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<CondenserEquipmentListExtensibleFields>(t_name) {} 
  CondenserEquipmentListExtensibleFields(int t_value) 
   : EnumBase<CondenserEquipmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "CondenserEquipmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CondenserEquipmentListExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<CondenserEquipmentListExtensibleFields>;
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
{ CondenserEquipmentListExtensibleFields::EquipmentObjectType, "EquipmentObjectType", "Equipment Object Type"},
{ CondenserEquipmentListExtensibleFields::EquipmentName, "EquipmentName", "Equipment Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const CondenserEquipmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CondenserEquipmentListExtensibleFields> OptionalCondenserEquipmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONDENSEREQUIPMENTLIST_FIELDENUMS_HXX
