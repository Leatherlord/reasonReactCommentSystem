(lang dune 3.8)

(using melange 0.1)

(name reasonReactCommentSystem)

(license "MIT")

(maintainers "Boyko Vladislav")

(authors "Boyko Vladislav")

(homepage https://github.com/Leatherlord/reasonReactCommentSystem)

(package
 (allow_empty)
 (name reasonReactCommentSystem)
 (synopsis "Functional programming fourth assignment")
 (description "Reason React simple comment system")
 (depends
  ocaml
  dune
  reson
  melange
  melange-fetch
  reason-react
  reason-react-ppx
  opam-check-npm-deps
  ocaml-lsp-server
  dot-merlin-reader
  odoc))
