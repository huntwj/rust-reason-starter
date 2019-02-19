[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type user = {
  id: int,
  name: string,
};

type state =
  | NotAsked
  | Loading
  | Failure
  | Loaded(list(user));

module Decode = {
  let user = user =>
    Json.Decode.{
      id: field("id", int, user),
      name: field("name", string, user),
    };
};
let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> {ReasonReact.string(message)} </h2>
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/app.re ")} </code>
        {ReasonReact.string("and save to reload.")}
      </p>
    </div>,
};
