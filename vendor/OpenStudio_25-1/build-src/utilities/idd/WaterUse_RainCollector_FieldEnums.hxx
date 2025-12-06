/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_WATERUSE_RAINCOLLECTOR_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERUSE_RAINCOLLECTOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterUse_RainCollectorFields
 *  \brief Enumeration of WaterUse:RainCollector's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterUse_RainCollectorFields, )
#else
class WaterUse_RainCollectorFields: public ::EnumBase<WaterUse_RainCollectorFields> {
 public: 
  enum domain 
  {
Name, StorageTankName, LossFactorMode, CollectionLossFactor, CollectionLossFactorScheduleName, MaximumCollectionRate,   };
  WaterUse_RainCollectorFields()
   : EnumBase<WaterUse_RainCollectorFields>(Name) {} 
  WaterUse_RainCollectorFields(const std::string &t_name) 
   : EnumBase<WaterUse_RainCollectorFields>(t_name) {} 
  WaterUse_RainCollectorFields(int t_value) 
   : EnumBase<WaterUse_RainCollectorFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_RainCollectorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_RainCollectorFields>::integer_value()); }
   private:
    friend class EnumBase<WaterUse_RainCollectorFields>;
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
{ WaterUse_RainCollectorFields::Name, "Name", "Name"},
{ WaterUse_RainCollectorFields::StorageTankName, "StorageTankName", "Storage Tank Name"},
{ WaterUse_RainCollectorFields::LossFactorMode, "LossFactorMode", "Loss Factor Mode"},
{ WaterUse_RainCollectorFields::CollectionLossFactor, "CollectionLossFactor", "Collection Loss Factor"},
{ WaterUse_RainCollectorFields::CollectionLossFactorScheduleName, "CollectionLossFactorScheduleName", "Collection Loss Factor Schedule Name"},
{ WaterUse_RainCollectorFields::MaximumCollectionRate, "MaximumCollectionRate", "Maximum Collection Rate"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_RainCollectorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_RainCollectorFields> OptionalWaterUse_RainCollectorFields ;
#endif

/** \class WaterUse_RainCollectorExtensibleFields
 *  \brief Enumeration of WaterUse:RainCollector's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(WaterUse_RainCollectorExtensibleFields, )
#else
class WaterUse_RainCollectorExtensibleFields: public ::EnumBase<WaterUse_RainCollectorExtensibleFields> {
 public: 
  enum domain 
  {
CollectionSurfaceName,   };
  WaterUse_RainCollectorExtensibleFields()
   : EnumBase<WaterUse_RainCollectorExtensibleFields>(CollectionSurfaceName) {} 
  WaterUse_RainCollectorExtensibleFields(const std::string &t_name) 
   : EnumBase<WaterUse_RainCollectorExtensibleFields>(t_name) {} 
  WaterUse_RainCollectorExtensibleFields(int t_value) 
   : EnumBase<WaterUse_RainCollectorExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_RainCollectorExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_RainCollectorExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<WaterUse_RainCollectorExtensibleFields>;
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
{ WaterUse_RainCollectorExtensibleFields::CollectionSurfaceName, "CollectionSurfaceName", "Collection Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_RainCollectorExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_RainCollectorExtensibleFields> OptionalWaterUse_RainCollectorExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERUSE_RAINCOLLECTOR_FIELDENUMS_HXX
