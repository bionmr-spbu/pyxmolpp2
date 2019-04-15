#include "../FCRA.h"
#include "xmol/polymer/Atom.h"
#include "xmol/utils/string.h"

void pyxmolpp::polymer::init_Chain(detail::FWD& fwd, pybind11::module &polymer) {

  using namespace xmol::polymer;
  (*fwd.pyChain)
      .def_property_readonly(
          "frame",
          [](ChainRef& chain) -> FrameRef { return FrameRef(static_cast<Chain&>(chain).frame()); },
          FrameRefPolicy,
          "Parent frame")

      .def(
          "__len__",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).size(); },
          "Returns number of residues in chain")

      .def(
          "__eq__",
          [](ChainRef& a, ChainRef& b) -> bool {
            return &static_cast<Chain&>(a) == &static_cast<Chain&>(b);
          })

      .def(
          "__getitem__",
          [](ChainRef& chain, ResidueId& rid) { return ResidueRef(static_cast<Chain&>(chain)[rid]); })

      .def(
          "__getitem__",
          [](ChainRef& chain, residueSerial_t& rid) {
            return ResidueRef(static_cast<Chain&>(chain)[ResidueId(rid)]);
          })

      .def_property_readonly(
          "size",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).size(); },
          "Returns number of residues in chain")

      .def_property_readonly(
          "index",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).index(); },
          "Chain index, starts from 0"
      )

      .def_property_readonly(
          "cIndex",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).index(); },
          "Chain index, starts from 0"
      )

      .def_property(
          "name",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).name(); },
          [](ChainRef& chain, ChainName value) { static_cast<Chain&>(chain).set_name(value); },
          "Chain name (chainID in PDB nomenclature)")

      .def_property("cName",
                    [](ChainRef& chain) { return static_cast<Chain&>(chain).name(); },
                    [](ChainRef& chain, ChainName value) { static_cast<Chain&>(chain).set_name(value); },
                    "Chain name (chainID in PDB nomenclature)")

      .def_property_readonly(
          "fIndex",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).frame().index(); },
          "Frame index"
      )

      .def_property_readonly(
          "asResidues",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).asResidues(); },
          "Returns selection of child residues")

      .def_property_readonly(
          "asAtoms",
          [](ChainRef& chain) { return static_cast<Chain&>(chain).asAtoms(); },
          "Returns selection of child atoms")

      .def(
          "emplace",
          [](ChainRef& chain, ResidueName name, residueId_t id, int reserve) -> ResidueRef {
            return ResidueRef(static_cast<Chain&>(chain).emplace(name, id, reserve));
          },
          ResidueRefPolicy,
          py::arg("name"),
          py::arg("id"),
          py::arg("reserve") = 0,
          "Adds an empty Residue to the end of chain")

      .def("emplace",
           [](ChainRef& chain, ResidueRef& r) -> ResidueRef {
             return ResidueRef(static_cast<Chain&>(chain).emplace(static_cast<Residue&>(r)));
           },
           ResidueRefPolicy,
           py::arg("residue"),
           "Adds a copy of given Residue to the end of chain")

      .def("delete",
           [](ChainRef& chain) { static_cast<Chain&>(chain).set_deleted(); },
           "Marks chain as deleted. Further access to deleted chain is illegal")

      .def(
          "__repr__",
          [](ChainRef& chain) {
            return "<pyxmolpp2.polymer.Chain index="
                + std::to_string(static_cast<Chain&>(chain).index())
                + " name=\""
                + static_cast<Chain&>(chain).name().str()
                + "\" at 0x"
                + xmol::utils::string::int2hex((uint64_t)(std::addressof(static_cast<Chain&>(chain))))
                + ">";
          });
  ;
}