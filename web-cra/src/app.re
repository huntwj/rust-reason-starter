[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type message = {
  id: int,
  text: string,
};

module Decode = {
  let message = message =>
    Json.Decode.{
      id: field("id", int, message),
      text: field("text", string, message),
    };

  let messages = json: list(message) => Json.Decode.list(message, json);
};

let url = "/api/v1/messages";

let fetchMessages = () =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json |> Decode.messages |> (messages => Some(messages) |> resolve)
       )
    |> catch(_err => resolve(None))
  );

type action =
  | LoadMessages
  | LoadedMessages(list(message))
  | LoadMessagesFailed;

type state =
  | NotAsked
  | Loading
  | Failure
  | Success(list(message));

let component = ReasonReact.reducerComponent("App");

let make = (~title, _children) => {
  ...component,
  initialState: () => NotAsked,
  reducer: (action, _state) =>
    switch (action) {
    | LoadMessages =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              fetchMessages()
              |> then_(result =>
                   switch (result) {
                   | Some(messages) =>
                     resolve(self.send(LoadedMessages(messages)))
                   | None => resolve(self.send(LoadMessagesFailed))
                   }
                 )
              |> ignore
            )
        ),
      )
    | LoadedMessages(messages) => ReasonReact.Update(Success(messages))
    | LoadMessagesFailed => ReasonReact.Update(Failure)
    },
  render: self =>
    <div className="App">
      <div className="App-header">
        <h2> {ReasonReact.string(title)} </h2>
        {
            switch (self.state) {
                | NotAsked =>
                    <p>
                        {ReasonReact.string("Not Asked")}
                        <br />
                        <button onClick=(_evt => self.send(LoadMessages))>
                            {ReasonReact.string("Load Messages")}
                        </button>
                    </p>
                | Loading => ReasonReact.string("Loading")
                | Success(messages) =>
                    <ul>
                    (
                        messages
                        |> List.map(message =>
                            <li key={string_of_int(message.id)}>
                                {ReasonReact.string(message.text)}
                            </li>
                            )
                        |> Array.of_list
                        |> ReasonReact.array
                    )
                    </ul>
                | Failure =>
                    <p>
                        {ReasonReact.string("Failure")}
                        <br />
                        <button onClick=(_evt => self.send(LoadMessages))>
                            {ReasonReact.string("Try again")}
                        </button>
                    </p>
            }
        }
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/app.re ")} </code>
        {ReasonReact.string("and save to reload.")}
      </p>
    </div>,
};
