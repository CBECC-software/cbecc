/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CONSTRUCTION_WINDOWEQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_CONSTRUCTION_WINDOWEQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Construction_WindowEquivalentLayerFields
 *  \brief Enumeration of Construction:WindowEquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Construction_WindowEquivalentLayerFields, )
#else
class Construction_WindowEquivalentLayerFields: public ::EnumBase<Construction_WindowEquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, OutsideLayer, Layer2, Layer3, Layer4, Layer5, Layer6, Layer7, Layer8, Layer9, Layer10, Layer11,   };
  Construction_WindowEquivalentLayerFields()
   : EnumBase<Construction_WindowEquivalentLayerFields>(Name) {} 
  Construction_WindowEquivalentLayerFields(const std::string &t_name) 
   : EnumBase<Construction_WindowEquivalentLayerFields>(t_name) {} 
  Construction_WindowEquivalentLayerFields(int t_value) 
   : EnumBase<Construction_WindowEquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_WindowEquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_WindowEquivalentLayerFields>::integer_value()); }
   private:
    friend class EnumBase<Construction_WindowEquivalentLayerFields>;
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
{ Construction_WindowEquivalentLayerFields::Name, "Name", "Name"},
{ Construction_WindowEquivalentLayerFields::OutsideLayer, "OutsideLayer", "Outside Layer"},
{ Construction_WindowEquivalentLayerFields::Layer2, "Layer2", "Layer 2"},
{ Construction_WindowEquivalentLayerFields::Layer3, "Layer3", "Layer 3"},
{ Construction_WindowEquivalentLayerFields::Layer4, "Layer4", "Layer 4"},
{ Construction_WindowEquivalentLayerFields::Layer5, "Layer5", "Layer 5"},
{ Construction_WindowEquivalentLayerFields::Layer6, "Layer6", "Layer 6"},
{ Construction_WindowEquivalentLayerFields::Layer7, "Layer7", "Layer 7"},
{ Construction_WindowEquivalentLayerFields::Layer8, "Layer8", "Layer 8"},
{ Construction_WindowEquivalentLayerFields::Layer9, "Layer9", "Layer 9"},
{ Construction_WindowEquivalentLayerFields::Layer10, "Layer10", "Layer 10"},
{ Construction_WindowEquivalentLayerFields::Layer11, "Layer11", "Layer 11"},
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
  inline std::ostream &operator<<(std::ostream &os, const Construction_WindowEquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_WindowEquivalentLayerFields> OptionalConstruction_WindowEquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONSTRUCTION_WINDOWEQUIVALENTLAYER_FIELDENUMS_HXX
