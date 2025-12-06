/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_BLDGDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_BLDGDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_BldgDataFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:BldgData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_BldgDataFields, )
#else
class GroundHeatTransfer_Basement_BldgDataFields: public ::EnumBase<GroundHeatTransfer_Basement_BldgDataFields> {
 public: 
  enum domain 
  {
DWALL_Wallthickness, DSLAB_Floorslabthickness, DGRAVXY_Widthofgravelpitbesidebasementwall, DGRAVZN_Graveldepthextendingabovethefloorslab, DGRAVZP_Graveldepthbelowthefloorslab,   };
  GroundHeatTransfer_Basement_BldgDataFields()
   : EnumBase<GroundHeatTransfer_Basement_BldgDataFields>(DWALL_Wallthickness) {} 
  GroundHeatTransfer_Basement_BldgDataFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_BldgDataFields>(t_name) {} 
  GroundHeatTransfer_Basement_BldgDataFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_BldgDataFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_BldgDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_BldgDataFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_BldgDataFields>;
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
{ GroundHeatTransfer_Basement_BldgDataFields::DWALL_Wallthickness, "DWALL_Wallthickness", "DWALL: Wall thickness"},
{ GroundHeatTransfer_Basement_BldgDataFields::DSLAB_Floorslabthickness, "DSLAB_Floorslabthickness", "DSLAB: Floor slab thickness"},
{ GroundHeatTransfer_Basement_BldgDataFields::DGRAVXY_Widthofgravelpitbesidebasementwall, "DGRAVXY_Widthofgravelpitbesidebasementwall", "DGRAVXY: Width of gravel pit beside basement wall"},
{ GroundHeatTransfer_Basement_BldgDataFields::DGRAVZN_Graveldepthextendingabovethefloorslab, "DGRAVZN_Graveldepthextendingabovethefloorslab", "DGRAVZN: Gravel depth extending above the floor slab"},
{ GroundHeatTransfer_Basement_BldgDataFields::DGRAVZP_Graveldepthbelowthefloorslab, "DGRAVZP_Graveldepthbelowthefloorslab", "DGRAVZP: Gravel depth below the floor slab"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_BldgDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_BldgDataFields> OptionalGroundHeatTransfer_Basement_BldgDataFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_BLDGDATA_FIELDENUMS_HXX
