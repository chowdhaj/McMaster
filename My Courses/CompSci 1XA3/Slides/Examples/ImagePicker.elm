module ImagePicker exposing (..)

import Html exposing (..)
import Html.Attributes exposing (..)
import Html.Events exposing (onClick)

import List exposing (..)
import Maybe exposing (..)

{- Model
   Stores a payload of image paths
 -}
type alias Model = { imgs : List String }

{- Statically encode image paths in initial model -}
init : Model
init = { imgs = ["Img1.jpg","Img2.jpg","Img3.jpg"]  }

{- Helper functions for selecting images -}
getImage : Model -> String
getImage model = case head model.imgs of
                     Just url -> url
                     Nothing -> ""

rotateRight : Model -> Model
rotateRight model = case model.imgs of
                       (x::xs) -> { model | imgs = xs ++ [x] }
                       []      -> { model | imgs = [] }

rotateLeft : Model -> Model
rotateLeft model = let
       n = length model.imgs - 1
    in { model | imgs = (drop n model.imgs) ++ (take n model.imgs) }

{- Update
   Move images to the top of the list based on Msg
 -}
type Msg = NextImage | PrevImage

update : Msg -> Model -> Model
update msg model = case msg of
                       NextImage -> rotateRight model
                       PrevImage -> rotateLeft model

{- View
   Pull image out of model to display and trigger
   NextImage and PrevImage with Html buttons
 -}
view : Model -> Html Msg
view model =
        div []
        [ button [ onClick NextImage ] [ text "Next" ]
        , button [ onClick PrevImage ] [ text "Prev" ]
        , div [] [img [src  <| getImage model] []]
        ]

{- Main -}
main : Program Never Model Msg
main = Html.beginnerProgram
          { model = init,
            view = view,
            update = update }

