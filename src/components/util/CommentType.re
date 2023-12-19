type t = {
  author: string,
  comment: string,
  time: Js.Date.t,
};

let decode = json => {
  Json.Decode.{
    author: json |> field("author", string),
    comment: json |> field("comment", string),
    time: json |> field("time", string) |> Js.Date.fromString,
  };
};
