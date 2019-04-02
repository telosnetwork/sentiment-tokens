# Sentiment Tokens Contract API

## Setup & Deployment

`./build.sh sentiment`

`./deploy sentiment local`

## Registration

Create a Sentiment Token profile by calling the `signup` action.

* `signup(name account_name)`

    `account_name` is the account name signing up for the platform.

## Activity

Interact with the platform by calling any of the following activity actions.

* `like(name from, name to)`

    `from` is the account sending the like.

    `to` is the account receiving the like.

* `dislike(name from, name to)`

    `from` is the account sending the dislike.

    `to` is the account receiving the dislike.
